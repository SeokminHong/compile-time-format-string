#ifndef CTFS_FIXED_STRING_HPP
#define CTFS_FIXED_STRING_HPP

#include <cstddef>

namespace ctfs {
template <size_t N> struct fixed_string {
  char content[N + 1] = {};
  size_t size = 0;

  constexpr fixed_string(const char (&input)[N]) noexcept {
    for (size_t i{0}; i < N; ++i) {
      if (input[i] == '\0') {
        size = i;
        return;
      }
      content[i] = input[i];
    }
  }

  constexpr fixed_string(const fixed_string &other) noexcept {
    for (size_t i{0}; i < N; ++i) {
      content[i] = other.content[i];
    }
    size = other.size;
  }

  constexpr const char &operator[](size_t n) const noexcept {
    return content[n];
  }
};
} // namespace ctfs

#endif // CTFS_FIXED_STRING_HPP