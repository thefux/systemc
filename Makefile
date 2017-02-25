GXX = g++


all: and_gate.o link


TestMain.o:
	g++ -c and_gate.cpp -I. -I/usr/local/systemc/include

link:
	g++ and_gate.o -o test -L. -L/usr/local/systemc/lib-linux64 -lsystemc

run:
	./test

clean:
	rm -rf and_gate.o
	rm -rf and_gate
	rm -rf and_gate.o
