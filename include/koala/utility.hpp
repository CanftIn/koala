#ifndef KOALA_UTILITY_HPP__
#define KOALA_UTILITY_HPP__

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace koala::utility
{
  struct StaticString {
    template <size_t N>
    constexpr StaticString(const char (&str)[N]) noexcept
      : _size(N - 1),
        _data(&str[0])
    { }

    constexpr size_t size() const noexcept { return _size; }

    

    const size_t _size;
    const char* _data = nullptr;
  };
} // namespace koala::utility



#endif
