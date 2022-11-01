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
#include "boxed_number.hpp"
#include "type_info.hpp"
#include "utility.hpp"

namespace koala
{
  namespace exception
  {
    class bad_boxed_cast : public std::bad_cast {
    public:
      bad_boxed_cast(TypeInfo t_from, const std::type_info &t_to, utility::StaticString t_what) noexcept
          : from(t_from)
          , to(&t_to)
          , m_what(std::move(t_what)) {
      }

      bad_boxed_cast(TypeInfo t_from, const std::type_info &t_to) noexcept
          : from(t_from)
          , to(&t_to)
          , m_what("Cannot perform boxed_cast") {
      }

      explicit bad_boxed_cast(utility::StaticString t_what) noexcept
          : m_what(std::move(t_what)) {
      }

      bad_boxed_cast(const bad_boxed_cast &) noexcept = default;
      ~bad_boxed_cast() noexcept override = default;

      /// \brief Description of what error occurred
      const char *what() const noexcept override { return m_what.c_str(); }

      TypeInfo from; ///< TypeInfo contained in the BoxedValue
      const std::type_info *to = nullptr; ///< std::type_info of the desired (but failed) result type

    private:
      utility::StaticString m_what;
    };
  } // namespace exception
  
  struct TypeConversionsState;

  namespace detail
  {
    template <typename T>
    constexpr T* throw_if_null(T* t) {
      if (t) return t;
      throw std::runtime_error("Attempted to dereference null BoxedValue");
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
                          T* ptr) {
      if (!ob.is_const() && ob.get_type_info().bare_equal_type_info(ti)) {
        return throw_if_null(ptr);
      }
    }

    template <typename Result>
    struct CastHelperInner {
      static Result cast(const BoxedValue& ob, const TypeConversionsState*) {
        return *static_cast<const Result*>(verify_type(ob, typeid(Result), ob.get_const_ptr()));
      }
    };

    template <typename Result>
    struct CastHelperInner<const Result> : CastHelperInner<Result>
    { };

    template<typename Result>
    struct CastHelperInner<const Result *> {
      static const Result *cast(const BoxedValue &ob, const TypeConversionsState *) {
        return static_cast<const Result *>(verify_type_no_throw(ob, typeid(Result), ob.get_const_ptr()));
      }
    };

    /// CastHelperInner for casting to a * type
    template<typename Result>
    struct CastHelperInner<Result *> {
      static Result *cast(const BoxedValue &ob, const TypeConversionsState *) {
        return static_cast<Result *>(verify_type_no_throw(ob, typeid(Result), ob.get_ptr()));
      }
    };

    template<typename Result>
    struct CastHelperInner<Result *const &> : public CastHelperInner<Result *> {
    };

    template<typename Result>
    struct CastHelperInner<const Result *const &> : public CastHelperInner<const Result *> {
    };

    /// CastHelperInner for casting to a & type
    template<typename Result>
    struct CastHelperInner<const Result &> {
      static const Result &cast(const BoxedValue &ob, const TypeConversionsState *) {
        return *static_cast<const Result *>(verify_type(ob, typeid(Result), ob.get_const_ptr()));
      }
    };

    /// CastHelperInner for casting to a & type
    template<typename Result>
    struct CastHelperInner<Result &> {
      static Result &cast(const BoxedValue &ob, const TypeConversionsState *) {
        return *static_cast<Result *>(verify_type(ob, typeid(Result), ob.get_ptr()));
      }
    };

    /// CastHelperInner for casting to a && type
    template<typename Result>
    struct CastHelperInner<Result &&> {
      static Result &&cast(const BoxedValue &ob, const TypeConversionsState *) {
        return std::move(*static_cast<Result *>(verify_type(ob, typeid(Result), ob.get_ptr())));
      }
    };

    /// CastHelperInner for casting to a std::unique_ptr<> && type
    /// \todo Fix the fact that this has to be in a shared_ptr for now
    template<typename Result>
    struct CastHelperInner<std::unique_ptr<Result> &&> {
      static std::unique_ptr<Result> &&cast(const BoxedValue &ob, const TypeConversionsState *) {
        return std::move(*(static_cast<std::shared_ptr<std::unique_ptr<Result>>>(ob.get())));
      }
    };

    /// CastHelperInner for casting to a std::unique_ptr<> & type
    /// \todo Fix the fact that this has to be in a shared_ptr for now
    template<typename Result>
    struct CastHelperInner<std::unique_ptr<Result> &> {
      static std::unique_ptr<Result> &cast(const BoxedValue &ob, const TypeConversionsState *) {
        return *(static_cast<std::shared_ptr<std::unique_ptr<Result>>>(ob.get()));
      }
    };

    /// CastHelperInner for casting to a std::unique_ptr<> & type
    /// \todo Fix the fact that this has to be in a shared_ptr for now
    template<typename Result>
    struct CastHelperInner<const std::unique_ptr<Result> &> {
      static std::unique_ptr<Result> &cast(const BoxedValue &ob, const TypeConversionsState *) {
        return *(static_cast<std::shared_ptr<std::unique_ptr<Result>>>(ob.get()));
      }
    };

    /// CastHelperInner for casting to a std::shared_ptr<> type
    template<typename Result>
    struct CastHelperInner<std::shared_ptr<Result>> {
      static auto cast(const BoxedValue &ob, const TypeConversionsState *) { return static_cast<std::shared_ptr<Result>>(ob.get()); }
    };

    /// CastHelperInner for casting to a std::shared_ptr<const> type
    template<typename Result>
    struct CastHelperInner<std::shared_ptr<const Result>> {
      static auto cast(const BoxedValue &ob, const TypeConversionsState *) {
        if (!ob.get_type_info().is_const()) {
          return std::const_pointer_cast<const Result>(static_cast<std::shared_ptr<Result>>(ob.get()));
        } else {
          return static_cast<std::shared_ptr<const Result>>(ob.get());
        }
      }
    };

    /// CastHelperInner for casting to a const std::shared_ptr<> & type
    template<typename Result>
    struct CastHelperInner<const std::shared_ptr<Result>> : CastHelperInner<std::shared_ptr<Result>> {
    };

    template<typename Result>
    struct CastHelperInner<const std::shared_ptr<Result> &> : CastHelperInner<std::shared_ptr<Result>> {
    };

    //template<typename Result>
    //struct CastHelperInner<std::shared_ptr<Result> &> {
    //  static_assert(!std::is_const<Result>::value, "Non-const reference to std::shared_ptr<const T> is not supported");
    //  static auto cast(const BoxedValue &ob, const TypeConversionsState *) {
    //    std::shared_ptr<Result> &res = static_cast<std::shared_ptr<Result>>(ob.get());
    //    return ob.pointer_sentinel(res);
    //  }
    //};

    /// CastHelperInner for casting to a const std::shared_ptr<const> & type
    template<typename Result>
    struct CastHelperInner<const std::shared_ptr<const Result>> : CastHelperInner<std::shared_ptr<const Result>> {
    };

    template<typename Result>
    struct CastHelperInner<const std::shared_ptr<const Result> &> : CastHelperInner<std::shared_ptr<const Result>> {
    };

    /// CastHelperInner for casting to a BoxedValue type
    template<>
    struct CastHelperInner<BoxedValue> {
      static BoxedValue cast(const BoxedValue &ob, const TypeConversionsState *) { return ob; }
    };

    /// CastHelperInner for casting to a BoxedValue & type
    template<>
    struct CastHelperInner<BoxedValue &> {
      static std::reference_wrapper<BoxedValue> cast(const BoxedValue &ob, const TypeConversionsState *) {
        return std::ref(const_cast<BoxedValue &>(ob));
      }
    };

    /// CastHelperInner for casting to a const BoxedValue & type
    template<>
    struct CastHelperInner<const BoxedValue> : CastHelperInner<BoxedValue> {
    };

    template<>
    struct CastHelperInner<const BoxedValue &> : CastHelperInner<BoxedValue> {
    };

    /// CastHelperInner for casting to a std::reference_wrapper type
    template<typename Result>
    struct CastHelperInner<std::reference_wrapper<Result>> : CastHelperInner<Result &> {
    };

    template<typename Result>
    struct CastHelperInner<const std::reference_wrapper<Result>> : CastHelperInner<Result &> {
    };

    template<typename Result>
    struct CastHelperInner<const std::reference_wrapper<Result> &> : CastHelperInner<Result &> {
    };

    template<typename Result>
    struct CastHelperInner<std::reference_wrapper<const Result>> : CastHelperInner<const Result &> {
    };

    template<typename Result>
    struct CastHelperInner<const std::reference_wrapper<const Result>> : CastHelperInner<const Result &> {
    };

    template<typename Result>
    struct CastHelperInner<const std::reference_wrapper<const Result> &> : CastHelperInner<const Result &> {
    };

    /// The exposed Cast_Helper object that by default just calls the CastHelperInner
    template<typename T>
    struct CastHelper {
      static decltype(auto) cast(const BoxedValue &ob, const TypeConversionsState *t_conversions) {
        return (CastHelperInner<T>::cast(ob, t_conversions));
      }
    };






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

    //template <typename From, typename To>
    //class StaticCaster {
    // public:
    //  static BoxedValue cast(const BoxedValue& t_from) {
    //    if (t_from.get_type_info().bare_equal(koala::user_type<From>())) {
    //      if (t_from.is_pointer()) {
//
    //      } else {
    //        if (t_from.is_const()) {
    //          const From& d = 
    //        }
    //      }
    //    }
    //  }
    //};
  } // namespace detail
  
  template<typename Type>
  decltype(auto) boxed_cast(const BoxedValue &bv, const TypeConversionsState *t_conversions = nullptr) {
    //if (!t_conversions || bv.get_type_info().bare_equal(user_type<Type>()) || (t_conversions && !(*t_conversions)->convertable_type<Type>())) {
    //  try {
    //    return detail::CastHelper<Type>::cast(bv, t_conversions);
    //  } catch (const koala::exception::bad_any_cast &) {
    //  }
    //}
//
    //if (t_conversions && (*t_conversions)->convertable_type<Type>()) {
    //  try {
    //    return (detail::CastHelper<Type>::cast((*t_conversions)->boxed_type_conversion<Type>(t_conversions->saves(), bv), t_conversions));
    //  } catch (...) {
    //    try {
    //      // try going the other way
    //      return (detail::CastHelper<Type>::cast((*t_conversions)->boxed_type_down_conversion<Type>(t_conversions->saves(), bv),
    //                                              t_conversions));
    //    } catch (const koala::exception::bad_any_cast &) {
    //      throw exception::bad_boxed_cast(bv.get_type_info(), typeid(Type));
    //    }
    //  }
    //} else {
    //  throw exception::bad_boxed_cast(bv.get_type_info(), typeid(Type));
    //}
    return detail::CastHelper<Type>::cast(BoxedValue(), nullptr);
  }
  
} // namespace koala



#endif
