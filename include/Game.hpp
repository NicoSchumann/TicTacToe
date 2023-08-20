#ifndef GAME_GUARD_HPP
#define GAME_GUARD_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Canvas.hpp"
#include <memory>


// foorward declarations
class Ai;
enum class Mark;
enum class State;


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

    /** This method shoulsd invoked by main(). */
    void run();

private:

    /** Resizes the button area. */
    void resize();

    void bye();

    sf::RenderWindow * m_window;
    Canvas m_canvas;
    Board m_board;
    std::array<sf::Rect<int>, 9> m_button;
    Mark m_currPlayer;
    State m_state; // State of Game
    int m_currButtonNo; //
    bool m_done;
    Mark m_aiPlayer;
    std::unique_ptr<Ai> m_ai;

};

#endif // GAME_GUARD_HPP
