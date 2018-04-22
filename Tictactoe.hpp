#ifndef TICTACTOE_GUARD
#define TICTACTOE_GUARD

#include <SFML/Graphics.hpp>
#include <array>
#include <string>

enum class Mark { empty, cross, ring };
enum class State { inProgress, cross, ring, draw };

class Board
{
public:
    Board();
    ~Board();

    /** Sets all fields of Board to Mark::empty */
    void reset();

    /** Sets a field of the Board class */
    void setMark( Mark mark, std::size_t field);

    /** Returns a Board's field value */
    Mark getMark( int position) const;

    /** Evaluates Board's state. */
    State evaluate() const;

private:
    std::array<Mark,9> m_fields;
};

class Canvas
{
public:
    Canvas(sf::RenderWindow*);
    ~Canvas();

    /** Draws all stuff. */
    void render();

    /** Updates the Canvas. */
    void update(Board &);

    /** Updates the Canvas on window's resize */
    void resize();

private:

    std::array<sf::RectangleShape,4> m_bar;
    sf::Texture m_texture;
    std::array<sf::Sprite,9> m_sprite;
    sf::RenderWindow * m_window;
};

// not yet implemented
class Ki
{
public:
    /** Returns the suggested Board's field number */
    int getButtonNo();
};

class Game
{
public:
    Game();
    Game(sf::RenderWindow *);
    ~Game();

    /** Let's choosing the player. Not yet implemented. */
    void intro();

    /** Waits for user input. */
    void handleInput();

    /** Updates the game state. */
    void update();

    /** Renders the canvas. */
    void render();

    /** Checks if the game is finish. */
    bool isDone() const;

    /**
     * Checks for intersection of mouse click position with
     * a TicTacToe draw field.
     *
     * @return The field from mouse position at mouse click.
     * If the mouse is not over a field, returns -1.
     */
    int getButtonNo(int posX, int posY) const;

    /** Returns which player is currently on move. */
    Mark getCurrPlayer() const;

    /** Toggles the current player. */
    void toggleCurrPlayer();

private:

    /** Resizes the button area. */
    void resize();

    sf::RenderWindow * m_window;
    Canvas m_canvas;
    Board m_board;
    std::array<sf::Rect<int>, 9> m_button;
    Mark m_currPlayer;
    State m_state; // State of Game
    int m_currButtonNo; //
    bool m_done;
    Mark m_kiPlayer;
    Ki * m_ki;

};

#endif // TICTACTOE_GUARD
