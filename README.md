# Compile Time Format String

A type-safe format string for `cstdio` powered by C++20.

[Live Demo](https://godbolt.org/z/6fdKqx8GM)

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
}
```

`g++-11 -std=c++20` required to build.

## NOTE

It supports `printf` only. Other functions (`sprintf`, `wprintf`, `scanf`, ...) will be supported.

## License

MIT
