#ifndef BOXED_VALUE_HPP__
#define BOXED_VALUE_HPP__

#include <map>
#include <any>
#include <memory>
#include <type_traits>

#include "define.hpp"
#include "type_info.hpp"

namespace koala
{
  class BoxedValue {
   public:
    struct VoidValue { };

   private:
    struct Data {
      Data(const TypeInfo& ti, std::any to, bool is_ref, const void* t_void_ptr, bool t_return_value)
        : _type_info(ti),
          _obj(std::move(to)),
          _data_ptr(ti.is_const() ? nullptr : const_cast<void*>(t_void_ptr)),
          _const_data_ptr(t_void_ptr),
          _is_ref(is_ref),
          _return_value(t_return_value)
      { }

      Data& operator = (const Data& rhs) {
        _type_info = rhs._type_info;
        _obj = rhs._obj;
        _is_ref = rhs._is_ref;
        _data_ptr = rhs._data_ptr;
        _const_data_ptr = rhs._const_data_ptr;
        _return_value = rhs._return_value;

        if (rhs._attrs) {
          _attrs = std::make_unique<std::map<std::string, std::shared_ptr<Data>>>(*rhs._attrs);
        }

        return *this;
      }

      Data(const Data&) = delete;

      Data(Data&&) = default;
      Data& operator = (Data&& rhs) = default;

      TypeInfo _type_info;
      std::any _obj;
      void* _data_ptr;
      const void* _const_data_ptr;
      std::unique_ptr<std::map<std::string, std::shared_ptr<Data>>> _attrs;
      bool _is_ref;
      bool _return_value;
    };

    struct ObjectData {
      //static auto get(BoxedValue::VoidValue, bool t_return_value) {
      //  return std::make_shared<Data>
      //}
    };

   public:
    // template <typename T, typename = std::enable_if_t<!std::is_same_v<BoxedValue, std::decay_t<T>>>>
    // explicit BoxedValue(T&& t, bool t_return_value = true)
    //   : _data(ObjectData::get(std::forward<T>(t), t_return_value));
    // { }

   private:
    //std::shared_ptr<Data> _data = ObjectData::get();
  };
} // namespace koala

#endif
