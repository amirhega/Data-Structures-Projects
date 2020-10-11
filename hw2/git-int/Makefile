all: gitint

gitint: gitint-shell.cpp
	g++ -g -Wall -std=c++11 gitint.h gitint.cpp gitint-shell.cpp -o gitint-shell

clean:
	rm gitint