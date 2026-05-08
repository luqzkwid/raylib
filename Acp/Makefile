all: main atomS

main : main.c
	gcc -o main main.c $(shell cat ../static/flags)

atomS : main.cpp
	g++ -std=c++23 -o atomS main.cpp log.cpp $(shell cat ../static/flags)
