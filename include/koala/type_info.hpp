#ifndef KOALA_TYPE_INFO_HPP__
#define KOALA_TYPE_INFO_HPP__

#include <type_traits>
#include <typeinfo>

namespace koala {
  namespace detail {
    template <typename T>
    struct BareType {
      using type = typename std::remove_cv_t<typename std::remove_pointer_t<typename std::remove_reference_t<T>>>;
    };

    template <typename T>
    using BareType_t = typename BareType<T>::type;
  } // namespace detail

  //class TypeInfo {
  // public:
  //  constexpr TypeInfo(const std::type_info* t_ti) noexcept
  //    : _type_info(t_ti)
  //  {}
//
  //  constexpr
//
  // private:
  //  struct UnknownType {};
  //  const std::type_info* _type_info = &typeid(UnknownType);
  //};
} // namespace koala

#endif
