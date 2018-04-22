#include <SFML/Graphics.hpp>
#include "Tictactoe.hpp"

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
