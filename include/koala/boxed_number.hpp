#ifndef KOALA_BOXED_NUMBER_HPP__
#define KOALA_BOXED_NUMBER_HPP__

#include "boxed_value.hpp"

namespace koala
{
  namespace exception
  {
    struct arithmetic_error : std::runtime_error {
      explicit arithmetic_error(const std::string &reason)
          : std::runtime_error("Arithmetic error: " + reason) {
      }
      arithmetic_error(const arithmetic_error &) = default;
      ~arithmetic_error() noexcept override = default;
    };
  } // namespace exception
  

  class BoxedNumber {
   private:
    enum class CommonTypes {
      T_UINT8,
      T_UINT16,
      T_UINT32,
      T_UINT64,
      T_INT8,
      T_INT16,
      T_INT32,
      T_INT64,
      T_DOUBLE,
      T_FLOAT,
      T_LONGDOUBLE
    };
    
    constexpr static CommonTypes get_common_type(size_t t_size, bool t_signed) noexcept {
      return (t_size == 1 && t_signed) ? (CommonTypes::T_INT8)
          : (t_size == 1)              ? (CommonTypes::T_UINT8)
          : (t_size == 2 && t_signed)  ? (CommonTypes::T_INT16)
          : (t_size == 2)              ? (CommonTypes::T_UINT16)
          : (t_size == 4 && t_signed)  ? (CommonTypes::T_INT32)
          : (t_size == 4)              ? (CommonTypes::T_UINT32)
          : (t_size == 8 && t_signed)  ? (CommonTypes::T_INT64)
                                       : (CommonTypes::T_UINT64);
    }

    static CommonTypes get_common_type(const BoxedValue& t_bv) {
      const TypeInfo& in_ti_ = t_bv.get_type_info();

      if (in_ti_ == user_type<int>()) {
        return get_common_type(sizeof(int), true);
      } else if (in_ti_ == user_type<double>()) {
        return CommonTypes::T_DOUBLE;
      } else if (in_ti_ == user_type<long double>()) {
        return CommonTypes::T_LONGDOUBLE;
      } else if (in_ti_ == user_type<float>()) {
        return CommonTypes::T_FLOAT;
      }
    }
  };
} // namespace koala

#endif
