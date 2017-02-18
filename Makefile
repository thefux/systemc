all: TestMain.o link


TestMain.o:
	g++ -c TestMain.cpp -I. -I/usr/local/systemc/include

link:
	g++ TestMain.o -o test -L. -L/usr/local/systemc/lib-linux64 -lsystemc

run:
	./test

clean:
	rm -rf test.o
	rm -rf test
	rm -rf TestMain.o
