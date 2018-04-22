#ifndef TICTACTOE_GUARD
#define TICTACTOE_GUARD

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

enum class Mark { empty, cross, ring };
enum class State { inProgress, cross, ring, draw };
enum class Player { cross, ring };

class Board
{
public:
    Board();
    ~Board();

    void reset();
    void setMark( Mark mark, std::size_t field);
    Mark getMark( int position) const;
    State evaluate() const;

private:
    std::array<Mark,9> m_fields;
};

class Canvas
{
public:
    Canvas(sf::RenderWindow*);
    ~Canvas();

    void render();
    void update(Board &);
    void resize();

private:
    std::array<sf::RectangleShape,4> m_bar;
    sf::Texture m_texture;
    std::array<sf::Sprite,9> m_sprite;
    sf::RenderWindow * m_window;
};

// not yet implemente
class Ki
{
public:
    int getButtonNo();
};

class Game
{
public:
    Game();
    Game(sf::RenderWindow *);
    ~Game();
    void intro();  // lets choosing a player // not yet implemente
    void handleInput(); // waits for user input
    void update();   // updates the game state
    void render();   // renders the canvas
    bool isDone() const;

    /**
     * Checks for intersection of mouse click position with
     * a TicTacToe draw field.
     *
     * @return The field from mouse position at mouse click.
     * If the mouse is not over a field, returns -1.
     */
    int getButtonNo(int posX, int posY) const; // returns window's field
    Mark getCurrPlayer() const;
    void toggleCurrPlayer();

private:
    void resize();
    sf::RenderWindow * m_window;
    Canvas m_canvas;
    Board m_board;
    std::array<sf::Rect<int>, 9> m_button;
    Mark m_currPlayer;
    State m_state; // State of Game
    int m_currButtonNo;
    bool m_done;
    Mark m_kiPlayer;
    Ki * m_ki;

};



#endif // TICTACTOE_GUARD
