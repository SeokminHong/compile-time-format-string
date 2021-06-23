#ifndef CTFS_TOKENIZER_HPP
#define CTFS_TOKENIZER_HPP

#include "fixed_string.hpp"
#include "types.hpp"

namespace ctfs {
template <Type type, LengthSpecifier length_spec, size_t next_pos>
struct parse_result {
  constexpr static Type _type = type;
  constexpr static LengthSpecifier _length_spec = length_spec;
  constexpr static size_t _next_pos = next_pos;
};

template <fixed_string str, size_t pos, char c, Type type,
          LengthSpecifier length_spec>
struct tokenizer {
  using result = parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>;
};

template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'd', type, length_spec> {
  using result = parse_result<Type::INTEGER, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 's', type, length_spec> {
  using result = parse_result<Type::CSTRING, length_spec, pos + 1>;
};
template <fixed_string str, size_t pos, Type type, LengthSpecifier length_spec>
struct tokenizer<str, pos, 'f', type, length_spec> {
  using result = parse_result<Type::DOUBLE, length_spec, pos + 1>;
};
} // namespace ctfs

#endif // CTFS_TOKENIZER_HPP