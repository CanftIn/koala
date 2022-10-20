#ifndef KOALA_DEFINE_HPP__
#define KOALA_DEFINE_HPP__

#include <string>
#include <vector>

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

} // namespace koala

#endif
