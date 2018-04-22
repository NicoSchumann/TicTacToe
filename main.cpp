#include <SFML/Graphics.hpp>
#include "Tictactoe.hpp"
#include <iostream>

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
}

/*
int main()
{
    Board board;
    sf::RenderWindow window(sf::VideoMode(300,300),"TicTacToe");
    Canvas canvas(&window);

    while (window.isOpen())
    {
        canvas.update(board);
        canvas.render();
        sf::Event event;
        while (window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            canvas.update(board);
            canvas.render();
        }
    }
}
*/
/*
int main()
{
    sf::Texture texture;
    if (!texture.loadFromFile("/home/nico/Pictures/sheets/64x32_tictactoe.png"))
    {
        std::cerr << "Texture file couldn't loaded!\n";
        return EXIT_FAILURE;
    }
    sf::Sprite cross(texture,sf::Rect<int>(0,0,32,32));
    cross.setPosition(0.0f,0.0f);

    sf::Sprite ring(texture);
    ring.setTextureRect( sf::Rect<int>(32,0,32, 32));
    ring.setPosition(32.0f, 0.0f );

    std::array<sf::Sprite,9> sprite;
    for( auto & sp : sprite)
    {
        sp = sf::Sprite(texture, sf::Rect<int>(0,0,32,32));
        sp.setPosition(100,100);
    }
    sf::RenderWindow window(sf::VideoMode(400, 400), "TicTacToe");

    while (window.isOpen())
    {
        window.clear();

        window.draw(cross);  // works
        window.draw(ring);  // works
        for (auto & sp : sprite) window.draw(sp); // doesn't work

        window.display();

        sf::Event event;

        while (window.waitEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
    return EXIT_SUCCESS;
}
*/
