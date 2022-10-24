#ifndef KOALA_ANY_HPP__
#define KOALA_ANY_HPP__

#include <utility>
#include <exception>

namespace koala
{
  namespace detail
  {
    namespace exception
    {
      class bad_any_cast : public std::bad_cast {
       public:
        const char* what() const noexcept override { return "bad any cast"; }
      };
    } // namespace exception
    
  } // namespace detail
  
} // namespace koala


#endif
