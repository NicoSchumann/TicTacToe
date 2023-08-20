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
    ~Game();

    /** This method should invoked by main(). */
    void run();

    /** Set puit. */
    void setDone();
    
    State getState() const;

    /** Resets the game */
    void reset();

    void receive(int);
    
   /** Waits for user input. */
    void handleInput();

private:

   /** Sets one player to this */
    void setRandomAI();
    void setMinimaxAI();
    void setNoAI();

    /** Here you could set one player at A.I. */
    void setAIPlayer(const Mark aiPlayer);

   /** Let's choosing the player. Not yet implemented. */
    void intro();

 
    /** Updates the game state. */
    void update();

    /** Renders the canvas. */
    void render();

    /** Checks if the game is finish. */
    bool isDone() const;


    
    /** Returns which player is currently on move. */
    Mark getCurrPlayer() const;

    /** Toggles the current player. */
    void toggleCurrPlayer();

    void bye();

    std::unique_ptr<Canvas> m_canvas;
    Board m_board;
    Mark m_currPlayer;
    State m_state; // State of Game
    int m_boardPosNo; // field-idx (0-8)
    bool m_done;
    Mark m_aiPlayer;
    std::unique_ptr<Ai> m_ai;

};

#endif // GAME_GUARD_HPP
