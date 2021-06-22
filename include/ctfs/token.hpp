#ifndef CTFS_TOKEN_HPP
#define CTFS_TOKEN_HPP

#include "type_list.hpp"

namespace ctfs {
template <char c0, char c1, typename list> struct token {
  constexpr static auto result = false;
  using types = list;
};

template <typename list> struct token<'%', 'd', list> {
  constexpr static auto result = true;
  using types = typename list::add<int>;
};

template <typename list> struct token<'%', 'f', list> {
  constexpr static auto result = true;
  using types = typename list::add<double>;
};

template <typename list> struct token<'%', 's', list> {
  constexpr static auto result = true;
  using types = typename list::add<const char *>;
};
} // namespace ctfs

#endif // CTFS_TOKEN_HPP