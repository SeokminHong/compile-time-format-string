#include "../include/ctfs.hpp"

int main() {
  ctfs::print<"Hello %d %s\n">(3, "world");
  ctfs::print<"value1: %03d, value2: %.2f\n">(5, 2.3f);
  int temp = 5;
  ctfs::print<"64bit-unsigned: %llu, pointer: %p\n">(UINT64_MAX, &temp);

  // error: invalid conversion from ‘const char*’ to ‘int’
  // ctfs::print<"This will fail to compile: %d %d\n">(3, "");
}