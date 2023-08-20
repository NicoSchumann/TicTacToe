#ifndef CANVAS_GUARD_HPP
#define CANVAS_GUARD_HPP

#include <SFML/Graphics.hpp>


class Board; // forward declaration

class Canvas
{
public:
    Canvas(sf::RenderWindow*);
    ~Canvas();

    /** Draws all stuff. */
    void render();

    /** Updates the Canvas. */
    void update(const Board &);

    /** Updates the Canvas on window's resize */
    void resize();

private:

    std::array<sf::RectangleShape,4> m_bar;
    sf::Texture m_texture;
    std::array<sf::Sprite,9> m_sprite;
    sf::RenderWindow * m_window;
};


#endif // CANVAS_GUARD_HPP