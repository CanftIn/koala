#ifndef KOALA_TYPE_CONVERSIONS_HPP__
#define KOALA_TYPE_CONVERSIONS_HPP__

#include <algorithm>
#include <atomic>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

#include "boxed_value.hpp"
#include "type_info.hpp"

namespace koala
{
  namespace detail
  {
    template <typename T>
    constexpr T* throw_if_null(T* t) {
      if (t) return t;
    }

    template <typename T>
    static const T* verify_type_no_throw(const BoxedValue& ob, const std::type_info& ti,
                                         const T* ptr) {
      if (ob.get_type_info() == ti) return ptr;
    }

    template <typename T>
    static T* verify_type_no_throw(const BoxedValue& ob, const std::type_info& ti,
                                   T* ptr) {
      if (!ob.is_const() && ob.get_type_info() == ti) return ptr;
    };

    template <typename T>
    static const T* verify_type(const BoxedValue& ob, const std::type_info& ti,
                                const T* ptr) {
      if (ob.get_type_info().bare_equal_type_info(ti)) {
        return throw_if_null(ptr);
      }
    }

    template <typename T>
    static T* verify_type(const BoxedValue& ob, const std::type_info& ti,
                          const T* ptr) {
      if (!ob.is_const() && ob.get_type_info().bare_equal_type_info(ti)) {
        return throw_if_null(ptr);
      }
    }

    struct TypeConversionsState;

    template <typename Result>
    struct CastHelperInner {
      static Result cast(const BoxedValue& ob, const TypeConversionsState*) {
        return *static_cast<const Result*>(verify_type(ob, typeid(Result), ob.get_const_ptr()));
      }
    };

    template <typename Result>
    struct CastHelperInner<const Result> : CastHelperInner<Result>
    { };








    class TypeConvertionBase {
     public:
      virtual BoxedValue convert(const BoxedValue& from) const = 0;
      virtual BoxedValue convert_down(const BoxedValue& to) const = 0;

      const TypeInfo& to() const noexcept { return _to; }
      const TypeInfo& from() const noexcept { return _from; }

      virtual bool bidir() const noexcept { return true; }

      virtual ~TypeConvertionBase() = default;

     protected:
      TypeConvertionBase(TypeInfo t_to, TypeInfo t_from)
        : _to(std::move(t_to)),
          _from(std::move(t_from))
      { }

     private:
      const TypeInfo _to;
      const TypeInfo _from;
    };

    template <typename From, typename To>
    class StaticCaster {
     public:
      static BoxedValue cast(const BoxedValue& t_from) {
        if (t_from.get_type_info().bare_equal(koala::user_type<From>())) {
          if (t_from.is_pointer()) {

          } else {
            if (t_from.is_const()) {
              const From& d = 
            }
          }
        }
      }
    };
  } // namespace detail
  
  
} // namespace koala



#endif
