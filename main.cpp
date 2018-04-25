#include <SFML/Graphics.hpp>
#include "Tictactoe.hpp"
#include <iostream> // debug

int main()
{
    Game game;
    game.intro();
    while(!game.isDone())
    {
        game.render();
        game.handleInput();
        game.update();
    }
    return EXIT_SUCCESS;
}

// for debugging proposals
/*
int main()
{
    Board board;
    board.setMark(Mark::cross,0);
    board.setMark(Mark::cross,1); // xxo
    board.setMark(Mark::ring,2);  // oxo
    board.setMark(Mark::ring,3);  // x--
    board.setMark(Mark::cross,4);
    board.setMark(Mark::ring,5);
    board.setMark(Mark::cross,6);
    //board.setMark(Mark::ring,7);
    //board.setMark(Mark::cross,8)

    std::cerr << board; // debug



    RandomAi * ai = new RandomAi(Mark::cross);
    int field = -1;
    //ai->playRandomField(board, Mark::cross);
    std::cerr << board;
    field = ai->getSuggestedField(board, Mark::cross);
    std::cerr << "Field:" << field << '\n';

    delete ai;
}
*/
