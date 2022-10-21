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

  class TypeInfo {
   public:
    constexpr TypeInfo(const bool t_is_const,
                       const bool t_is_reference,
                       const bool t_is_pointer,
                       const bool t_is_void,
                       const bool t_is_arithmetic,
                       const std::type_info* t_ti,
                       const std::type_info* t_bare_ti) noexcept
      : _type_info(t_ti),
        _bare_type_info(t_bare_ti),
        _flags((static_cast<unsigned int>(t_is_const) << is_const_flag)
                + (static_cast<unsigned int>(t_is_reference) << is_reference_flag)
                + (static_cast<unsigned int>(t_is_pointer) << is_pointer_flag)
                + (static_cast<unsigned int>(t_is_void) << is_void_flag)
                + (static_cast<unsigned int>(t_is_arithmetic) << is_arithmetic_flag))
    {}

    constexpr TypeInfo() noexcept = default;

    bool operator < (const TypeInfo& ti) const noexcept {
      return _type_info->before(*ti._type_info);
    }

    constexpr bool operator != (const TypeInfo& ti) const noexcept {
      return !(operator==(ti));
    }

    constexpr bool operator != (const std::type_info& ti) const noexcept {
      return !(operator==(ti));
    }

    constexpr bool operator == (const TypeInfo& ti) const noexcept {
      return ti._type_info == _type_info || *ti._type_info == *_type_info;
    }

    constexpr bool operator == (const std::type_info& ti) const noexcept {
      return !is_undef() && (*_type_info) == ti;
    }

    constexpr bool is_const() const noexcept { return (_flags & (1 << is_const_flag)) != 0; }
    constexpr bool is_reference() const noexcept { return (_flags & (1 << is_reference_flag)) != 0; }
    constexpr bool is_void() const noexcept { return (_flags & (1 << is_void_flag)) != 0; }
    constexpr bool is_arithmetic() const noexcept { return (_flags & (1 << is_arithmetic_flag)) != 0; }
    constexpr bool is_undef() const noexcept { return (_flags & (1 << is_undef_flag)) != 0; }
    constexpr bool is_pointer() const noexcept { return (_flags & (1 << is_pointer_flag)) != 0; }

    const char* name() const noexcept {
      if (!is_undef()) {
        return _type_info->name();
      } else {
        return "";
      }
    }

    const char* bare_name() const noexcept {
      if (!is_undef()) {
        return _bare_type_info->name();
      } else {
        return "";
      }
    }

   private:
    struct UnknownType {};
    [[maybe_unused]] const std::type_info* _type_info = &typeid(UnknownType);
    [[maybe_unused]] const std::type_info* _bare_type_info = &typeid(UnknownType);
    static const int is_const_flag = 0;
    static const int is_reference_flag = 1;
    static const int is_pointer_flag = 2;
    static const int is_void_flag = 3;
    static const int is_arithmetic_flag = 4;
    static const int is_undef_flag = 5;
    unsigned int _flags = (1 << is_undef_flag);
  };
} // namespace koala

#endif
