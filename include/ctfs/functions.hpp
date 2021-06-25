#ifndef CTFS_FUNCTIONS_HPP
#define CTFS_FUNCTIONS_HPP

#include "fixed_string.hpp"
#include "type_list.hpp"
#include <cstddef>
#include <cstdio>

namespace ctfs {
template <fixed_string str, typename... Args> struct functions;

template <fixed_string str, typename... Args>
struct functions<str, type_list<Args...>> {
  static int print(Args... args) { return printf(str.content, args...); }
  static int sprint(char *s, Args... args) {
    return sprintf(s, str.content, args...);
  }
  static int fprint(FILE *f, Args... args) {
    return fprintf(f, str.content, args...);
  }
};
} // namespace ctfs

#endif // CTFS_FUNCTIONS_HPP