#ifndef GUI_GUARD
#define GUI_GUARD

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Ai.hpp"


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

    /** Resets the game */
    void reset();

    /**
     * Checks for intersection of mouse click position with
     * a TicTacToe draw field.
     *
     * @return The field from mouse position at mouse click.
     * If the mouse is not over a field, returns -1.
     */
    int getButtonNo(const int posX, const int posY) const;

    /** Returns which player is currently on move. */
    Mark getCurrPlayer() const;

    /** Toggles the current player. */
    void toggleCurrPlayer();

    /** Sets one player to this */
    void setRandomAI();
    void setMinimaxAI();
    void setNoAI();

    /** Here you could set one player at A.I. */
    void setAIPlayer(const Mark aiPlayer);

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
    Mark m_aiPlayer;
    Ai * m_ai;

};

#endif // GUI_GUARD
