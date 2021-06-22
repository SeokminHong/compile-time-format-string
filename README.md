# Compile Time Format String

A type-safe format string for `cstdio` powered by C++20.

[Live Demo](https://godbolt.org/z/dY3EzGo3f)

## Usage

```C++
#include "include/ctfs.hpp"

int main()
{
  ctfs::print<"Hello %d %s\n">(3, "world");
  ctfs::print<"value1: %d, value2: %f\n">(5, 2.3f);

  // error: invalid conversion from ‘const char*’ to ‘int’
  ctfs::print<"This will fail to compile: %d %d\n">(3, "");
}
```

It only works for `gcc-11`.

## NOTE

It only supports simple format strings like `%d`, `%f`, and `%s`.

## License

MIT
