#ifndef KOALA_KOALA_COMMON_HPP__
#define KOALA_KOALA_COMMON_HPP__

#include <algorithm>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_set>

#include "type_info.hpp"
#include "boxed_value.hpp"
#include "utility.hpp"

namespace koala
{
  struct ASTNode;

  enum TokenKind : unsigned short {
#define TOK(X) X,
#include "reserved_word.def"
    NUM_TOKENS
  };

  const char* get_token_name(TokenKind kind) {
    switch (kind) {
#define TOK_MATCH(X, Y) case X: return Y;
#include "reserved_word.def"
      default: break;
    }
    return nullptr;
  }

  struct NameValidator {
    template <typename T>
    static bool is_reserved_word(const T& s) noexcept {
      const static std::unordered_set<std::uint32_t> words;
      for (auto e = 0; e < TokenKind::NUM_TOKENS; ++e) {
        words.insert(utility::hash(get_token_name(e)));
      }
      return words.count(utility.hash(s)) == 1;
    }

    template <typename T>
    static bool valid_object_name(const T& name) noexcept {
      return name.find("::") == std::string::npos && !is_reserved_word(name);
    }
  };
  
} // namespace koala


#endif