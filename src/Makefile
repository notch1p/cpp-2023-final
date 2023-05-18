CXX = clang++-16
CXXFLAGS := -O2
export CXXFLAGS

all:main
	-ln -s main bookstore
main: book.o csv.o interface.o user.o exec.o main.cpp
csv.o:csv.hpp csv.cpp
exec.o:exec.hpp exec.cpp
user.o:user.hpp user.cpp
book.o:book.hpp book.cpp
clean:
	-rm -rf *.o
clear:
	-rm -rf main *.o bookstore