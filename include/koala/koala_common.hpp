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
#include "koala_impl.hpp"

namespace koala
{
  struct ASTNode;

  enum AstNodeType : unsigned short {
#define AST_NODE_TYPE(X) X,
//#include "reserved_word.def"
AST_NODE_TYPE(Id)
AST_NODE_TYPE(Fun_Call)
AST_NODE_TYPE(Unused_Return_Fun_Call)
AST_NODE_TYPE(Arg_List)
AST_NODE_TYPE(Equation)
AST_NODE_TYPE(Var_Decl)
AST_NODE_TYPE(Assign_Decl)
AST_NODE_TYPE(Array_Call)
AST_NODE_TYPE(Dot_Access)
AST_NODE_TYPE(Lambda)
AST_NODE_TYPE(Block)
AST_NODE_TYPE(Scopeless_Block)
AST_NODE_TYPE(Def)
AST_NODE_TYPE(While)
AST_NODE_TYPE(If)
AST_NODE_TYPE(For)
AST_NODE_TYPE(Ranged_For)
AST_NODE_TYPE(Inline_Array)
AST_NODE_TYPE(Inline_Map)
AST_NODE_TYPE(Return)
AST_NODE_TYPE(File)
AST_NODE_TYPE(Prefix)
AST_NODE_TYPE(Break)
AST_NODE_TYPE(Continue)
AST_NODE_TYPE(Map_Pair)
AST_NODE_TYPE(Value_Range)
AST_NODE_TYPE(Inline_Range)
AST_NODE_TYPE(Try)
AST_NODE_TYPE(Catch)
AST_NODE_TYPE(Finally)
AST_NODE_TYPE(Method)
AST_NODE_TYPE(Attr_Decl)
AST_NODE_TYPE(Logical_And)
AST_NODE_TYPE(Logical_Or)
AST_NODE_TYPE(Reference)
AST_NODE_TYPE(Switch)
AST_NODE_TYPE(Case)
AST_NODE_TYPE(Default)
AST_NODE_TYPE(Noop)
AST_NODE_TYPE(Class)
AST_NODE_TYPE(Binary)
AST_NODE_TYPE(Arg)
AST_NODE_TYPE(Global_Decl)
AST_NODE_TYPE(Constant)
AST_NODE_TYPE(Compiled)
    AST_NODE_NUMS
  };

  static const char* const node_type_names[] = {
#define AST_NODE_TYPE_MATCH(X, Y) Y,
//#include "reserved_word.def"
AST_NODE_TYPE_MATCH(Id                             , "Id")
AST_NODE_TYPE_MATCH(Fun_Call                       , "Fun_Call")
AST_NODE_TYPE_MATCH(Unused_Return_Fun_Call         , "Unused_Return_Fun_Call")
AST_NODE_TYPE_MATCH(Arg_List                       , "Arg_List")
AST_NODE_TYPE_MATCH(Equation                       , "Equation")
AST_NODE_TYPE_MATCH(Var_Decl                       , "Var_Decl")
AST_NODE_TYPE_MATCH(Assign_Decl                    , "Assign_Decl")
AST_NODE_TYPE_MATCH(Array_Call                     , "Array_Call")
AST_NODE_TYPE_MATCH(Dot_Access                     , "Dot_Access")
AST_NODE_TYPE_MATCH(Lambda                         , "Lambda")
AST_NODE_TYPE_MATCH(Block                          , "Block")
AST_NODE_TYPE_MATCH(Scopeless_Block                , "Scopeless_Block")
AST_NODE_TYPE_MATCH(Def                            , "Def")
AST_NODE_TYPE_MATCH(While                          , "While")
AST_NODE_TYPE_MATCH(If                             , "If")
AST_NODE_TYPE_MATCH(For                            , "For")
AST_NODE_TYPE_MATCH(Ranged_For                     , "Ranged_For")
AST_NODE_TYPE_MATCH(Inline_Array                   , "Inline_Array")
AST_NODE_TYPE_MATCH(Inline_Map                     , "Inline_Map")
AST_NODE_TYPE_MATCH(Return                         , "Return")
AST_NODE_TYPE_MATCH(File                           , "File")
AST_NODE_TYPE_MATCH(Prefix                         , "Prefix")
AST_NODE_TYPE_MATCH(Break                          , "Break")
AST_NODE_TYPE_MATCH(Continue                       , "Continue")
AST_NODE_TYPE_MATCH(Map_Pair                       , "Map_Pair")
AST_NODE_TYPE_MATCH(Value_Range                    , "Value_Range")
AST_NODE_TYPE_MATCH(Inline_Range                   , "Inline_Range")
AST_NODE_TYPE_MATCH(Try                            , "Try")
AST_NODE_TYPE_MATCH(Catch                          , "Catch")
AST_NODE_TYPE_MATCH(Finally                        , "Finally")
AST_NODE_TYPE_MATCH(Method                         , "Method")
AST_NODE_TYPE_MATCH(Attr_Decl                      , "Attr_Decl")
AST_NODE_TYPE_MATCH(Logical_And                    , "Logical_And")
AST_NODE_TYPE_MATCH(Logical_Or                     , "Logical_Or")
AST_NODE_TYPE_MATCH(Reference                      , "Reference")
AST_NODE_TYPE_MATCH(Switch                         , "Switch")
AST_NODE_TYPE_MATCH(Case                           , "Case")
AST_NODE_TYPE_MATCH(Default                        , "Default")
AST_NODE_TYPE_MATCH(Noop                           , "Noop")
AST_NODE_TYPE_MATCH(Class                          , "Class")
AST_NODE_TYPE_MATCH(Binary                         , "Binary")
AST_NODE_TYPE_MATCH(Arg                            , "Arg")
AST_NODE_TYPE_MATCH(Global_Decl                    , "Global_Decl")
AST_NODE_TYPE_MATCH(Constant                       , "Constant")
AST_NODE_TYPE_MATCH(Compiled                       , "Compiled")
    nullptr
  };

  std::string get_node_type_name(AstNodeType kind) {
    if (kind < AstNodeType::AST_NODE_NUMS) {
      return std::string(node_type_names[kind]);
    }
    return nullptr;
  }

  enum class OperatorPrecedence {
#define Operator_Precedence(X) X,
//#include "reserved_word.def"
Operator_Precedence(Ternary_Cond)
Operator_Precedence(Logical_Or)
Operator_Precedence(Logical_And)
Operator_Precedence(Bitwise_Or)
Operator_Precedence(Bitwise_Xor)
Operator_Precedence(Bitwise_And)
Operator_Precedence(Equality)
Operator_Precedence(Comparison)
Operator_Precedence(Shift)
Operator_Precedence(Addition)
Operator_Precedence(Multiplication)
Operator_Precedence(Prefix)
    OP_NUMS
  };

  enum TokenKind : unsigned short {
#define TOK(X) X,
//#include "reserved_word.def"
TOK(tk_def)
TOK(tk_fun)
TOK(tk_while)
TOK(tk_for)
TOK(tk_if)
TOK(tk_else)
TOK(tk_ampamp)
TOK(tk_pipepipe)
TOK(tk_comma)
TOK(tk_auto)
TOK(tk_return)
TOK(tk_break)
TOK(tk_true)
TOK(tk_false)
TOK(tk_flass)
TOK(tk_attr)
TOK(tk_var)
TOK(tk_global)
TOK(tk_upper_global)
TOK(tk_underline)
TOK(tk_upper_line)
TOK(tk_upper_file)
TOK(tk_upper_func)
TOK(tk_upper_class)
    NUM_TOKENS
  };

  static const char* const tok_names[] = {
#define TOK_MATCH(X, Y) Y,
//#include "reserved_word.def"
TOK_MATCH(tk_def,               "def")
TOK_MATCH(tk_fun,               "fun")
TOK_MATCH(tk_while,             "while")
TOK_MATCH(tk_for,               "for")
TOK_MATCH(tk_if,                "if")
TOK_MATCH(tk_else,              "else")
TOK_MATCH(tk_ampamp,            "&&")
TOK_MATCH(tk_pipepipe,          "||")
TOK_MATCH(tk_comma,             ",")
TOK_MATCH(tk_auto,              "auto")
TOK_MATCH(tk_return,            "return")
TOK_MATCH(tk_break,             "break")
TOK_MATCH(tk_true,              "true")
TOK_MATCH(tk_false,             "false")
TOK_MATCH(tk_flass,             "class")
TOK_MATCH(tk_attr,              "attr")
TOK_MATCH(tk_var,               "var")
TOK_MATCH(tk_global,            "global")
TOK_MATCH(tk_upper_global,      "GLOBAL")
TOK_MATCH(tk_underline,         "_")
TOK_MATCH(tk_upper_line,        "__LINE__")
TOK_MATCH(tk_upper_file,        "__FILE__")
TOK_MATCH(tk_upper_func,        "__FUNC__")
TOK_MATCH(tk_upper_class,       "__CLASS__")
    nullptr
  };

  std::string get_token_name(TokenKind kind) {
    if (kind < TokenKind::NUM_TOKENS) {
      return std::string(tok_names[kind]);
    }
    return nullptr;
  }

  struct NameValidator {
    template <typename T>
    static bool is_reserved_word(const T& s) noexcept {
      static std::unordered_set<std::uint32_t> words;
      for (auto e = 0; e < TokenKind::NUM_TOKENS; ++e) {
        words.insert(utility::hash(::koala::get_token_name(static_cast<TokenKind>(e))));
      }
      return words.count(utility::hash(s)) == 1;
    }

    template <typename T>
    static bool valid_object_name(const T& name) noexcept {
      return name.find("::") == std::string::npos && !is_reserved_word(name);
    }

    template <typename T>
    static void validate_object_name(const T& name) {
      if (is_reserved_word(name)) {
        throw exception::reserved_word_error(std::string(name));
      }
      if (name.find("::") != std::string::npos) {
        throw exception::illegal_name_error(std::string(name));
      }
    }
  };
  
} // namespace koala


#endif