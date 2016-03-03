CFLAGS=-W -Wall

all: usps

test: test.o p1fxns.o
	cc -o test test.o p1fxns.o 

test.o: test.c p1fxns.h 

clean:
	rm -f *.o usps test

usps: usps.o p1fxns.o uspsList.o
	cc -o usps usps.o p1fxns.o uspsList.o

usps.o: usps.c p1fxns.h uspsList.h

p1fxns.o: p1fxns.h
	gcc -c p1fxns.c

uspsList.o: uspsList.h
	gcc -c uspsList.c


