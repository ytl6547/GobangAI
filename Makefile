CC       = g++
CPPFLAGS = -std=c++11
all: gobang

gobang.o: gobang.h gobang.cpp
	$(CC) $(CPPFLAGS) -c gobang.cpp -o gobang.o

gobang: gobang.o main.cpp
	$(CC) $(CPPFLAGS) gobang.o main.cpp -o gobang

.PHONY: clean

clean:
	rm TicTacToe.o
	rm TicTacToe