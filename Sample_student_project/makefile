
# Reilly Zink 2.14.18

all : main.o game.o othello.o
	g++ main.o game.o othello.o
	tar -cvf ZinkHW5archive.tar .
main.o : main.cc othello.h game.h
	cc -c main.cc
game.o : game.cc game.h
	cc -c game.cc
othello.o : othello.cc othello.h
	cc -c othello.cc

clean:
	-rm -f *.o core *.core
