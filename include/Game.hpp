#ifndef GAME_GUARD_HPP
#define GAME_GUARD_HPP

#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "Canvas.hpp"

// foorward declarations
class Ai;
enum class Mark;
enum class State;


enum class AIState
{
    none,
    playerA,
    playerB,
    both
};

enum class AIMode
{
    none,
    random,
    minimax
};

class Game
{
public:
    Game();
    ~Game();

    /** Invoke this to run the game. */
    void run();

    /** Resets the game */
    void reset();

    /** For receiving a board field number (0 - 8) */
    void receive(int boardFieldNo);

    /** Toggles between no AI, random AI and minimax AI. */
    void toggleAI();

    /** Toggles, which player is controlled by AI. */
    void toggleAIState();

private:
    /** Sets the the used AI. */
    void setRandomAI();
    void setMinimaxAI();
    void setNoAI();

   /** Here you can set none, one or both players to AI. */
    void setAIState(AIState);

    /** Let the AI make its turn. */
    void processAI();

    /** Toggles the current player. */
    void toggleCurrPlayer();

    std::unique_ptr<Canvas> m_canvas;
    Board m_board;
    Mark m_currPlayer; // Flags the current player.
    State m_state;     // State of Game.
    std::unique_ptr<Ai> m_ai;
    AIState m_aiState; // Flags, wich player is controlled by AI
    AIMode m_aiMode;   // Flags, wich AI is in use.
};

#endif // GAME_GUARD_HPP
