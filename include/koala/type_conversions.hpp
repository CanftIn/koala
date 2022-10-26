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
  namespace exception
  {
    class conversion_error : public bad_boxed_cast {

    };
  } // namespace exception
  
} // namespace koala



#endif
