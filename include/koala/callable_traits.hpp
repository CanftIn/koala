#ifndef KOALA_CALLABLE_TRAITS_HPP__
#define KOALA_CALLABLE_TRAITS_HPP__

#include <memory>

namespace koala
{
  namespace detail
  {
    template <typename Class, typename... Param>
    struct Constructor {
      template <typename... Inner>
      std::shared_ptr<Class> operator () (Inner&&... inner) const {
        return std::make_shared<Class>(std::forward<Inner>(inner)...);
      }
    };
  } // namespace detail
  
} // namespace koala


#endif
