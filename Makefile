CXX=g++
CFLAGS=-g -Wall -O3
CXX_STANDARD=-std=c++20

example: examples/main.cpp
	$(CXX) $(CFLAGS) $(CXX_STANDARD) examples/main.cpp -o main
