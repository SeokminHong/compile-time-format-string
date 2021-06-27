#include "../include/ctfs.hpp"

int main() {
  ctfs::print<"Hello %d %s\n">(3, "world");

  ctfs::print<"value1: %03d, value2: %.2f\n">(5, 2.3f);

  int temp = 5;
  ctfs::print<"64bit-unsigned: %llu, pointer: %p\n">(UINT64_MAX, &temp);

  // error: invalid conversion from ‘const char*’ to ‘int’
  // ctfs::print<"This will fail to compile: %d %d\n">(3, "");

  char s[256]{};
  ctfs::sprint<"sprint %u %f">(s, -1, 3.14);
  puts(s);

  // error: too few arguments to function
  // ctfs::sprint<"fail to compile: %s %s">(s, "Hello");

  FILE *f = fopen("./main.txt", "w");

  ctfs::fprint<"fprint %g %c">(f, 2.718, 'a' + 1);

  // error: too many arguments to function
  // ctfs::fprint<"fprint %d %d %d">(f, 1, 2, 3, 4);

  fclose(f);

  int a, b;
  ctfs::scan<"%d %d">(&a, &b);
  ctfs::print<"%#x (%d) %#x (%d)\n">(a, a, b, b);
}