# Compile Time Format String

Type-safe format string I/O functions similar to cstdio interfaces using C++20.

[Live Demo](https://godbolt.org/z/TGe3rjbKK)

## Usage

```C++
#include "include/ctfs.hpp"

int main()
{
  // Prints "Hello 3 world".
  ctfs::print<"Hello %d %s\n">(3, "world");
  // Prints "value1: 005, value2: 2.30".
  ctfs::print<"value1: %03d, value2: %.2f\n">(5, 2.3f);

  int temp = 5;
  // Prints "64bit-unsigned: 18446744073709551615, pointer: 0x...".
  ctfs::print<"64bit-unsigned: %llu, pointer: %p\n">(UINT64_MAX, &temp);

  // error: invalid conversion from ‘const char*’ to ‘int’
  ctfs::print<"This will fail to compile: %d %d\n">(3, "");


  char s[256]{};
  // Write "sprint 4294967295 3.140000" to the buffer `s`.
  ctfs::sprint<"sprint %u %f">(s, -1, 3.14);
  puts(s);

  // error: too few arguments to function
  // ctfs::sprint<"fail to compile: %s %s">(s, "Hello");

  FILE *f = fopen("./main.txt", "w");
  // cat main.txt: "fprint 2.718 b"
  ctfs::fprint<"fprint %g %c">(f, 2.718, 'a' + 1);

  // error: too many arguments to function
  // ctfs::fprint<"fprint %d %d %d">(f, 1, 2, 3, 4);

  fclose(f);
}
```

`g++-11 -std=c++20` required to build.

## NOTE

It supports `printf`, `sprintf`, and `fprintf` only. stdin functions (`scanf`, `sscanf`, ...) and wchar functions (`wprintf`, ...) will be supported.

## License

MIT
