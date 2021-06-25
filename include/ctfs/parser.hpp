#ifndef CTFS_PARSER_HPP
#define CTFS_PARSER_HPP

#include "fixed_string.hpp"
#include "token.hpp"
#include <cstddef>
#include <type_traits>

namespace ctfs {
template <fixed_string str, typename pos, typename list> struct parser {
  static constexpr size_t pos_val = pos::value;
  using parse_result = token<str, pos_val, list>;
  using result =
      typename parser<str,
                      std::integral_constant<size_t, parse_result::next_pos>,
                      typename parse_result::types>::result;
};

template <fixed_string str, typename list>
struct parser<str, std::integral_constant<size_t, str.size - 1>, list> {
  using result = list;
};

template <fixed_string str, typename list>
struct parser<str, std::integral_constant<size_t, str.size>, list> {
  using result = list;
};
} // namespace ctfs

#endif // CTFS_PARSER_HPP