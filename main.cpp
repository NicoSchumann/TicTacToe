#include "GUI.hpp"

//
//  Reset the board with right mouse click!
//

int main()
{
    Game game;

    game.setMinimaxAI();  // chose your A.I.
    //game.setRandomAI();
    // game.setNoAI()

    game.intro(); // not yet implemented
    while(!game.isDone())
    {
        game.render();
        game.handleInput();
        game.update();
    }
    return EXIT_SUCCESS;
}
