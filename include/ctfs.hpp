#ifndef CTFS_HPP
#define CTFS_HPP

#include "ctfs/functions.hpp"
#include "ctfs/parser.hpp"
#include "ctfs/type_list.hpp"

namespace ctfs {
template <fixed_string str> struct execute {
  using types =
      parser<str, std::integral_constant<size_t, 0>, type_list<>>::result;
  static constexpr auto print = &functions<str, types>::print;
  static constexpr auto sprint = &functions<str, types>::sprint;
  static constexpr auto fprint = &functions<str, types>::fprint;
};

template <fixed_string str> const static auto print = execute<str>::print;
template <fixed_string str> const static auto sprint = execute<str>::sprint;
template <fixed_string str> const static auto fprint = execute<str>::fprint;
} // namespace ctfs

#endif // CTFS_HPP