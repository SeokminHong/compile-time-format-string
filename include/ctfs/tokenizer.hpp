#ifndef CTFS_TOKENIZER_HPP
#define CTFS_TOKENIZER_HPP

#include "fixed_string.hpp"
#include "types.hpp"
#include <algorithm>
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

template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, '\0', Type::NONE, length_spec> {
  using result = parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>;
};

/** Length Subspecifiers */
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 'h', Type::NONE, LengthSpecifier::NONE> {
  using result = std::conditional_t<
      str[pos + 1] == 'h',
      typename tokenizer<str, pos + 2, str[pos + 2], Type::NONE,
                         LengthSpecifier::hh>::result,
      typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                         LengthSpecifier::h>::result>;
};
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 'l', Type::NONE, LengthSpecifier::NONE> {
  using result = std::conditional_t<
      str[pos + 1] == 'l',
      typename tokenizer<str, pos + 2, str[pos + 2], Type::NONE,
                         LengthSpecifier::ll>::result,
      typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                         LengthSpecifier::l>::result>;
};
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 'j', Type::NONE, LengthSpecifier::NONE> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::j>::result;
};
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 'z', Type::NONE, LengthSpecifier::NONE> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::z>::result;
};
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 't', Type::NONE, LengthSpecifier::NONE> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::t>::result;
};
template <fixed_string str, size_t pos>
struct tokenizer<str, pos, 'L', Type::NONE, LengthSpecifier::NONE> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::L>::result;
};

/** INTEGER */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'd', Type::NONE, length_spec> {
  using result = parse_result<Type::INTEGER, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'i', Type::NONE, length_spec> {
  using result = parse_result<Type::INTEGER, length_spec, pos + 1>;
};

/** UNSIGNED */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'u', Type::NONE, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'o', Type::NONE, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'x', Type::NONE, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'X', Type::NONE, length_spec> {
  using result = parse_result<Type::UNSIGNED, length_spec, pos + 1>;
};

/** DOUBLE */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'a', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'A', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'e', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'E', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'f', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'F', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'g', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'G', Type::NONE, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};

/** CHAR */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'c', Type::NONE, length_spec> {
  using result = parse_result<Type::CHAR, length_spec, pos + 1>;
};

/** CSTRING */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 's', Type::NONE, length_spec> {
  using result = parse_result<Type::CSTRING, length_spec, pos + 1>;
};

/** POINTER */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'p', Type::NONE, length_spec> {
  using result = parse_result<Type::POINTER, length_spec, pos + 1>;
};

/** NOTHING */
template <fixed_string str, size_t pos, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'n', Type::NONE, length_spec> {
  using result = parse_result<Type::NOTHING, length_spec, pos + 1>;
};
} // namespace ctfs

#endif // CTFS_TOKENIZER_HPP