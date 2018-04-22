TicTacToe : Tictactoe.o main.o
	c++ -o TicTacToe Tictactoe.o main.o -lsfml-system -lsfml-window -lsfml-graphics

Tictactoe.o: Tictactoe.cpp Tictactoe.hpp
	c++ -std=c++11 -c Tictactoe.cpp
	
main.o : main.cpp Tictactoe.hpp
	c++ -std=c++11 -c main.cpp

clean:
	rm -f Tictactoe.o main.o TicTacToe
