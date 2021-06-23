#ifndef CTFS_TYPES_HPP
#define CTFS_TYPES_HPP

#include <cstddef>
#include <cstdint>
#include <cwctype>

namespace ctfs {
enum class Type : uint8_t {
  NONE,
  INTEGER,
  UNSIGNED,
  DOUBLE,
  CHAR,
  CSTRING,
  POINTER,
  NOTHING
};

enum class LengthSpecifier : uint8_t { NONE, hh, h, l, ll, j, z, t, L };

template <Type type, LengthSpecifier length_spec> struct type_specifier {
  constexpr static bool result = false;
};

/** INTEGER */
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = int;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::hh> {
  constexpr static bool result = true;
  using type = signed char;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::h> {
  constexpr static bool result = true;
  using type = short int;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::l> {
  constexpr static bool result = true;
  using type = long int;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::ll> {
  constexpr static bool result = true;
  using type = long long int;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::j> {
  constexpr static bool result = true;
  using type = intmax_t;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::z> {
  constexpr static bool result = true;
  using type = size_t;
};
template <> struct type_specifier<Type::INTEGER, LengthSpecifier::t> {
  constexpr static bool result = true;
  using type = ptrdiff_t;
};

/** UNSIGNED */
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = unsigned int;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::hh> {
  constexpr static bool result = true;
  using type = unsigned char;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::h> {
  constexpr static bool result = true;
  using type = unsigned short int;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::l> {
  constexpr static bool result = true;
  using type = unsigned long int;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::ll> {
  constexpr static bool result = true;
  using type = unsigned long long int;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::j> {
  constexpr static bool result = true;
  using type = uintmax_t;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::z> {
  constexpr static bool result = true;
  using type = size_t;
};
template <> struct type_specifier<Type::UNSIGNED, LengthSpecifier::t> {
  constexpr static bool result = true;
  using type = ptrdiff_t;
};

/** DOUBLE */
template <> struct type_specifier<Type::DOUBLE, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = double;
};
template <> struct type_specifier<Type::DOUBLE, LengthSpecifier::L> {
  constexpr static bool result = true;
  using type = long double;
};

/** CHAR */
template <> struct type_specifier<Type::CHAR, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = int;
};
template <> struct type_specifier<Type::CHAR, LengthSpecifier::l> {
  constexpr static bool result = true;
  using type = wint_t;
};

/** CSTRING */
template <> struct type_specifier<Type::CSTRING, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = char const *;
};
template <> struct type_specifier<Type::CSTRING, LengthSpecifier::l> {
  constexpr static bool result = true;
  using type = wchar_t *;
};

/** POINTER */
template <> struct type_specifier<Type::POINTER, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = void *;
};

/** NOTHING */
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::NONE> {
  constexpr static bool result = true;
  using type = int *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::hh> {
  constexpr static bool result = true;
  using type = signed char const *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::h> {
  constexpr static bool result = true;
  using type = short int *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::l> {
  constexpr static bool result = true;
  using type = long int *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::ll> {
  constexpr static bool result = true;
  using type = long long int *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::j> {
  constexpr static bool result = true;
  using type = intmax_t *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::z> {
  constexpr static bool result = true;
  using type = size_t *;
};
template <> struct type_specifier<Type::NOTHING, LengthSpecifier::t> {
  constexpr static bool result = true;
  using type = ptrdiff_t *;
};
} // namespace ctfs

#endif // CTFS_TYPES_HPP