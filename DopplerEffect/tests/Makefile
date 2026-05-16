all : test_1 test_2 test_3

test_1 : test_1.cpp
	g++ -o test_1 test_1.cpp

test_2 : test_2.cpp
	g++ -std=c++23 -o test_2 test_2.cpp $(shell cat ../../static/flags)

test_3 : test_3.cpp
	g++ -std=c++23 -o test_3 test_3.cpp
