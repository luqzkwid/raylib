all: atomC atomCPP

atomC : Satom.c
	gcc -o atomC Satom.c $(shell cat ../static/flags)

atomCPP : Satom.cpp
	g++ -std=c++23 -o atomCPP Satom.cpp log.cpp $(shell cat ../static/flags)
