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
      TUINT8,
      TUINT16,
      TUINT32,
      TUINT64,
      TINT8,
      TINT16,
      TINT32,
      TINT64,
      TDOUBLE,
      TFLOAT
    };
    
  };
} // namespace koala

#endif
