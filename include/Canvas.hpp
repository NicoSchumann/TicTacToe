#ifndef CANVAS_GUARD_HPP
#define CANVAS_GUARD_HPP

#include <SFML/Graphics.hpp>
#include <memory>


class Board; // forward declaration

class Canvas
{
public:
    Canvas();
    ~Canvas();

    /** Draws all stuff. */
    void render();

    /** Updates the Canvas. */
    void update(const Board &);

    void setGameHandle(Game *);
 
    /** Closes the window */
    void close();

private:

    /** Updates the Canvas on window's resize */
    void resize();

    /**
     * Checks for intersection of mouse click position with
     * a TicTacToe draw field.
     *
     * @return The field from mouse position at mouse click.
     * If the mouse is not over a field, returns -1.
     */
    int getBoardPosNo(const int posX, const int posY) const;


    void handleInput();

    Game * m_game;
    std::shared_ptr<sf::RenderWindow> m_window;
    std::array<sf::RectangleShape,4> m_bars;
    sf::Texture m_texture;
    std::array<sf::Sprite,9> m_sprites;
    std::array<sf::Rect<int>, 9> m_buttons;

};


#endif // CANVAS_GUARD_HPP