CXX = clang++
CXXFLAGS := -O2 -std=c++17 -static
export CXXFLAGS

all:main
main: book.o csv.o interface.o user.o exec.o main.cpp
csv.o:csv.hpp csv.cpp
exec.o:exec.hpp exec.cpp
user.o:user.hpp user.cpp
book.o:book.hpp book.cpp
clean:
	-rm -rf *.o
clear:
	-rm -rf main *.o bookstore
