test: include/protocol/*.hpp tests/catch.hpp tests/test.cpp
	clang++ -std=c++11 -I include tests/test.cpp -o test

clean:
	rm test
