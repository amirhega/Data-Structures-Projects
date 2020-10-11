all: expr-tester

expr-tester: expr-tester.cpp expr-ops.o expr-reader.o
	g++ -g -std=gnu++11 -Wall expr-tester.cpp expr-ops.o expr-reader.o -o expr-tester

expr-ops.o: expr-ops.cpp expr-ops.h expr-reader.h
	g++ -g -std=gnu++11 -Wall -c expr-ops.cpp -o expr-ops.o

expr-reader.o: expr-reader.cpp expr-reader.h
	g++ -g -std=gnu++11 -Wall -c expr-reader.cpp -o expr-reader.o

clean:
	rm -f *.o expr-tester