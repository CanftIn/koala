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

    constexpr const char* c_str() const noexcept { return _data; }

    constexpr auto begin() const noexcept { return _data; }

    constexpr auto end() const noexcept { return _data + _size; }

    constexpr bool operator == (std::string_view other) const noexcept {
      auto b1 = begin();
      const auto e1 = end();
      auto b2 = other.begin();
      const auto e2 = other.end();

      if (e1 - b1 != e2 - b2) {
        return false;
      }

      while (b1 != e1) {
        if (*b1 != *b2) {
          return false;
        }
        ++b1;
        ++b2;
      }
      return true;
    }

    bool operator==(const std::string &t_str) const noexcept {
      return std::equal(begin(), end(), std::cbegin(t_str), std::cend(t_str));
    }

    const size_t _size;
    const char* _data = nullptr;
  };
} // namespace koala::utility



#endif
