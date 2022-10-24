#ifndef KOALA_DEFINE_HPP__
#define KOALA_DEFINE_HPP__

#include <string>
#include <vector>
#include <type_traits>

#define KOALA_COMPILER_VERSION __VERSION__

namespace koala {

  constexpr static const int version_major = 0;
  constexpr static const int version_minor = 1;
  constexpr static const char *compiler_version = KOALA_COMPILER_VERSION;

  struct BuildInfo {
    [[nodiscard]] constexpr static int version_major() noexcept { return koala::version_major; }

    [[nodiscard]] constexpr static int version_minor() noexcept { return koala::version_minor; }

    [[nodiscard]] static std::string version() {
      return std::to_string(version_major()) + '.' + std::to_string(version_minor());
    }

    [[nodiscard]] static std::string compiler_version() { return koala::compiler_version; }
  };

  template <typename T>
  [[nodiscard("parse_num")]] constexpr auto parse_num(const std::string_view t_str) noexcept
    -> typename std::enable_if_t<std::is_integral_v<T>, T> {
    T t;
    for (const auto c : t_str) {
      if (c < '0' || c > '9') {
        return t;
      }
      t *= 10;
      t += c - '0';
    }
    return t;
  }

} // namespace koala

#endif
