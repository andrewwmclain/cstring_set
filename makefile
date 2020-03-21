CFLAGS = -std=c++14 -Wall -g

set:    cstringset.o main.o 
	g++ cstringset.o main.o -o set $(CFLAGS)

test:	unit-test.o cstringset.o test.o
	g++ unit-test.o cstringset.o test.o -o test $(CFLAGS)

main.o:	main.cpp cstringset.h 
	g++ -c main.cpp $(CFLAGS)

cstringset.o:	cstringset.cpp cstringset.h
	g++ -c cstringset.cpp $(CFLAGS)

unit-test.o:	unit-test.cpp cstringset.h 
	g++ -c unit-test.cpp $(CFLAGS)

test.o:	test.cpp test.h
	g++ -c test.cpp $(CFLAGS)

clean:
	rm -f test set *.o

