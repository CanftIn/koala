#include <algorithm>
#include <map>

template <class Cond, class T1>
struct If_Then;

template <class Cond, class T1, class T2>
struct If_Then_Else;

template <class K, class F>
struct Switch {
  using Key = K;
  using Func = std::function<F>;
  using RetT = typename Func::result_type;

  class Case {
   public:
    Case(const Key& k, const Func& func) : _key(k), _func(func) { }

    Key _key;
    Func _func;
  };

  class Default {
   public:
    Default(const Func& func) : _func(func) { }

    Func _func;
  };
 private:
  using FuncMap = std::map<Key, Func>;
  using FuncMapEntry = typename FuncMap::value_type;

 public:
  template <class... Args>
  Switch(const Args& ... args) { AddCase(args...); }

  template <class... Args>
  RetT operator () (const Key& k, const Args&... args) const {
    return Call<RetT>(k, args...);
  }

  RetT operator () (const Key& k) const {
    return Call<RetT>(k);
  }

 private:
  void AddCase(const Case& entry) { _funcs.insert(FuncMapEntry(entry._key, entry._func)); }
  void AddCase(const Default& entry) { _default = entry._func; }
  
  template <class... Args>
  void AddCase(const Case& entry, const Args& ... args) {
    AddCase(entry);
    AddCase(args...);
  }

  template <class Ret, class... Args>
  Ret Call(const Key& k, const Args&... args) const {
    if (_funcs.find(k) != _funcs.end()) return _funcs.find(k)->second(args...);
    else if (_default) return _default(args...);
    return Ret();
  }
  template <>
  void Call(const Key& k) const {
    if (_funcs.find(k) != _funcs.end()) return _funcs.find(k)->second();
    else if (_default) return _default();
  }
  FuncMap _funcs;
  Func _default;
};