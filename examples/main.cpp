#include "../include/ctfs.hpp"

int main() {
  ctfs::print<"Hello %d %s\n">(3, "world");
  ctfs::print<"value1: %03d, value2: %0.2f\n">(5, 2.3f);

  // error: invalid conversion from ‘const char*’ to ‘int’
  // ctfs::print<"This will fail to compile: %d %d\n">(3, "");
}