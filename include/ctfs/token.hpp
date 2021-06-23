#ifndef CTFS_TOKEN_HPP
#define CTFS_TOKEN_HPP

#include "fixed_string.hpp"
#include "type_list.hpp"

namespace ctfs {
enum class ParseResult {
  NONE,
  INTEGER,
  UNSIGNED,
  LONG,
  CHAR,
  POINTER,
  CSTRING,
  DOUBLE,
  INVALID
};
template <size_t N>
constexpr ParseResult parse(const fixed_string<N> &str, size_t pos) {
  char c = str[pos];
  if (c == 'd' || c == 'i' || c == 'o' || c == 'x' || c == 'X')
    return ParseResult::INTEGER;
  if (c == 'u')
    return ParseResult::UNSIGNED;
  if (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'f' || c == 'F' ||
      c == 'g' || c == 'G')
    return ParseResult::DOUBLE;
  if (c == 's')
    return ParseResult::CSTRING;
  if (c == 'c')
    return ParseResult::CHAR;
  if (c == 'p')
    return ParseResult::POINTER;
  return ParseResult::INVALID;
}

template <ParseResult result, typename list> struct result_analizer;
template <typename... Args>
struct result_analizer<ParseResult::NONE, type_list<Args...>> {
  constexpr static size_t step = 1;
  using types = type_list<Args...>;
};
template <typename... Args>
struct result_analizer<ParseResult::INTEGER, type_list<Args...>> {
  constexpr static size_t step = 2;
  using types = type_list<Args..., int>;
};
template <typename... Args>
struct result_analizer<ParseResult::DOUBLE, type_list<Args...>> {
  constexpr static size_t step = 2;
  using types = type_list<Args..., double>;
};
template <typename... Args>
struct result_analizer<ParseResult::CSTRING, type_list<Args...>> {
  constexpr static size_t step = 2;
  using types = type_list<Args..., char const *>;
};
template <typename... Args>
struct result_analizer<ParseResult::INVALID, type_list<Args...>> {
  constexpr static size_t step = 2;
  using types = type_list<Args...>;
};

template <fixed_string str, size_t pos, char cur> struct tokenizer {
  constexpr static ParseResult parse_result = ParseResult::NONE;
};

template <fixed_string str, size_t pos> struct tokenizer<str, pos, '%'> {
  constexpr static ParseResult parse_result = parse(str, pos + 1);
};

template <fixed_string str, size_t pos, typename list> struct token;

template <fixed_string str, size_t pos, typename... Args>
struct token<str, pos, type_list<Args...>> {
  constexpr static ParseResult parse_result =
      tokenizer<str, pos, str[pos]>::parse_result;
  using result = result_analizer<parse_result, type_list<Args...>>;
  constexpr static size_t next_pos = pos + result::step;
  using types = typename result::types;
};
} // namespace ctfs

#endif // CTFS_TOKEN_HPP