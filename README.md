# Compile Time Format String

A type-safe format string for `cstdio` powered by C++20.

[Live Demo](https://godbolt.org/z/dY3EzGo3f)

## Usage

```C++
#include "include/ctfs.hpp"

int main()
{
  // Prints "Hello 3 world".
  ctfs::print<"Hello %d %s\n">(3, "world");
  // Prints "value1: 005, value2: 2.30".
  ctfs::print<"value1: %03d, value2: %.2f\n">(5, 2.3f);

  // error: invalid conversion from ‘const char*’ to ‘int’
  ctfs::print<"This will fail to compile: %d %d\n">(3, "");
}
```

It only works for `gcc-11`.

## NOTE

It supports `printf` only. Also the length sub-specifiers (e.g. `lld`, `lu`) are not supported yet.

## License

MIT
