#ifndef CTFS_TOKEN_HPP
#define CTFS_TOKEN_HPP

#include "fixed_string.hpp"
#include "tokenizer.hpp"
#include "type_list.hpp"
#include "types.hpp"

namespace ctfs {
enum class IOType : uint8_t { STDIN, STDOUT };
template <typename T, IOType io_type> struct get_type {
  using type =
      std::conditional_t<io_type == IOType::STDIN, std::add_pointer_t<T>, T>;
};

template <fixed_string str, size_t pos, char cur> struct get_token {
  using result = parse_result<Type::NONE, LengthSpecifier::NONE, pos + 1>;
};

template <fixed_string str, size_t pos> struct get_token<str, pos, '%'> {
  using result = typename tokenizer<str, pos + 1, str[pos + 1], Type::NONE,
                                    LengthSpecifier::NONE>::result;
};

template <bool success, IOType io_type, typename type_specifier, typename list>
struct type_list_getter;
template <typename type_specifier, IOType io_type, typename list>
struct type_list_getter<false, io_type, type_specifier, list> {
  using types = list;
};
template <Type type, LengthSpecifier length_spec, IOType io_type,
          typename... Args>
struct type_list_getter<true, io_type, type_specifier<type, length_spec>,
                        type_list<Args...>> {
  using type_result = type_specifier<type, length_spec>::type;
  using types = type_list<
      Args..., std::conditional_t<type != Type::NOTHING,
                                  typename get_type<type_result, io_type>::type,
                                  type_result>>;
};

template <fixed_string str, size_t pos, IOType io_type, typename list>
struct token;

template <fixed_string str, size_t pos, IOType io_type, typename... Args>
struct token<str, pos, io_type, type_list<Args...>> {
  using result = typename get_token<str, pos, str[pos]>::result;
  using type_result = type_specifier<result::_type, result::_length_spec>;
  constexpr static size_t next_pos = result::_next_pos;
  using types =
      typename type_list_getter<type_result::result, io_type, type_result,
                                type_list<Args...>>::types;
};
} // namespace ctfs

#endif // CTFS_TOKEN_HPP