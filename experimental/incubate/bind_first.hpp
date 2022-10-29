#include <type_traits>
#include <utility>

template <typename F, typename T>
struct bind_first {
  F f;
  T t;
  template <typename... Args>
  auto operator () (Args&&... args) const
    -> decltype(f(t, std::forward<Args>(args)...))
  {
    return f(t, std::forward<Args>(args)...);
  }
};

template <typename F, typename T>
bind_first<typename std::decay_t<F>,
           typename std::decay_t<T>>
BindFirst_cpp11(F&& f, T&& t) {
  return { std::forward<F>(f), std::forward<T>(t) };
}

template <typename F, typename T>
auto BindFirst_cpp14(F&& f, T&& t) {
  return [f = std::forward<F>(f), t = std::forward<T>(t)] (auto&&... args) {
    return f(t, std::forward<decltype(args)>(args)...);
  };
}

template <typename O, typename Ret, typename P1, typename... Param>
constexpr auto BindFirst_new(Ret (*f)(P1, Param...), O&& o) {
  return [f, o = std::forward<O>(o)] (Param... param) -> Ret {
    return f(o, std::forward<Param>(param)...);
  };
}