#ifndef CTFS_TOKENIZER_HPP
#define CTFS_TOKENIZER_HPP

#include "fixed_string.hpp"
#include "types.hpp"
#include <algorithm>
#include <array>
#include <type_traits>

namespace ctfs {
template <Type type, LengthSpecifier length_spec, size_t next_pos>
struct parse_result {
  constexpr static Type _type = type;
  constexpr static LengthSpecifier _length_spec = length_spec;
  constexpr static size_t _next_pos = next_pos;
};

constexpr static char flags[]{'-', '+', ' ', '#', '0', '1', '2', '3',
                              '4', '5', '6', '7', '8', '9', '*', '.'};
template <size_t N> constexpr size_t get_length(char const (&)[N]) { return N; }
constexpr size_t flag_size = get_length(flags);

template <fixed_string str, size_t pos, char c, Type type,
          LengthSpecifier length_spec>
struct tokenizer {
  constexpr static bool is_flag =
      std::find(flags, flags + flag_size, c) != flags + flag_size;
  using result = std::conditional_t<
      is_flag,
      typename tokenizer<str, pos + 1, str[pos + 1], type, length_spec>::result,
      parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>>;
};

template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, '\0', type, length_spec> {
  using result = parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>;
};

/** INTEGER */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'd', type, length_spec> {
  using result = parse_result<Type::INTEGER, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'i', type, length_spec> {
  using result = parse_result<Type::INTEGER, length_spec, pos + 1>;
};

/** UNSIGNED */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'u', type, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'o', type, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'x', type, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'X', type, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};

/** DOUBLE */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'a', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'A', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'e', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'E', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'f', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'F', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'g', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'G', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};

/** CHAR */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'c', type, length_spec> {
  using result = parse_result<Type::CHAR, length_spec, pos + 1>;
};

/** CSTRING */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 's', type, length_spec> {
  using result = parse_result<Type::CSTRING, length_spec, pos + 1>;
};

/** POINTER */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'p', type, length_spec> {
  using result = parse_result<Type::POINTER, length_spec, pos + 1>;
};

/** NOTHING */
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'n', type, length_spec> {
  using result = parse_result<Type::NOTHING, length_spec, pos + 1>;
};
} // namespace ctfs

#endif // CTFS_TOKENIZER_HPP