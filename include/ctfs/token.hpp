#ifndef CTFS_TOKEN_HPP
#define CTFS_TOKEN_HPP

#include "fixed_string.hpp"
#include "tokenizer.hpp"
#include "type_list.hpp"
#include "types.hpp"

namespace ctfs {
template <fixed_string str, size_t pos, char cur> struct get_token {
  using result = parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>;
};

template <fixed_string str, size_t pos> struct get_token<str, pos, '%'> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::NONE>::result;
};

template <bool success, typename type_specifier, typename list>
struct type_list_getter;
template <typename type_specifier, typename list>
struct type_list_getter<false, type_specifier, list> {
  using types = list;
};
template <typename type_specifier, typename... Args>
struct type_list_getter<true, type_specifier, type_list<Args...>> {
  using types = type_list<Args..., typename type_specifier::type>;
};

template <fixed_string str, size_t pos, typename list> struct token;

template <fixed_string str, size_t pos, typename... Args>
struct token<str, pos, type_list<Args...>> {
  using result = typename get_token<str, pos, str[pos]>::result;
  using type_result = type_specifier<result::_type, result::_length_spec>;
  constexpr static size_t next_pos = result::_next_pos;
  using types = typename type_list_getter<type_result::result, type_result,
                                          type_list<Args...>>::types;
};
} // namespace ctfs

#endif // CTFS_TOKEN_HPP