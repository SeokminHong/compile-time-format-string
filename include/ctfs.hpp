#ifndef CTFS_HPP
#define CTFS_HPP

#include "ctfs/functions.hpp"
#include "ctfs/parser.hpp"
#include "ctfs/type_list.hpp"

namespace ctfs {
template <fixed_string str> struct execute {
  using stdin_types = parser<str, std::integral_constant<size_t, 0>,
                             IOType::STDIN, type_list<>>::result;
  static constexpr auto scan = &functions<str, stdin_types>::scan;
  static constexpr auto sscan = &functions<str, stdin_types>::sscan;
  static constexpr auto fscan = &functions<str, stdin_types>::fscan;

  using stdout_types = parser<str, std::integral_constant<size_t, 0>,
                              IOType::STDOUT, type_list<>>::result;
  static constexpr auto print = &functions<str, stdout_types>::print;
  static constexpr auto sprint = &functions<str, stdout_types>::sprint;
  static constexpr auto fprint = &functions<str, stdout_types>::fprint;
};

template <fixed_string str> constexpr static auto scan = execute<str>::scan;
template <fixed_string str> constexpr static auto sscan = execute<str>::sscan;
template <fixed_string str> constexpr static auto fscan = execute<str>::fscan;

template <fixed_string str> constexpr static auto print = execute<str>::print;
template <fixed_string str> constexpr static auto sprint = execute<str>::sprint;
template <fixed_string str> constexpr static auto fprint = execute<str>::fprint;
} // namespace ctfs

#endif // CTFS_HPP