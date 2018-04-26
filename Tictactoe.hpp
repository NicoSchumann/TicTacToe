#ifndef TICTACTOE_GUARD
#define TICTACTOE_GUARD

#include <SFML/Graphics.hpp>
#include <array>
#include <string>
#include <iostream>

enum class Mark { empty, cross, ring };
enum class State { inProgress, cross, ring, draw };

/** Overloads the << operator, so that enums could be printed to console. */
std::ostream& operator<<(std::ostream &, const Mark);
std::ostream & operator<<( std::ostream &, const State);
class Board; // forward declaration
std::ostream & operator<<(std::ostream &, const Board&);


class Board
{
public:
    Board();
    Board(const Board &);

    /** Sets all fields of Board to Mark::empty */
    void reset();

    /** Sets a field of the Board class */
    void setMark( Mark mark, std::size_t field);

    /** Returns a Board's field value */
    Mark getMark(const int position) const;

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
    void update(const Board &);

    /** Updates the Canvas on window's resize */
    void resize();

private:

    std::array<sf::RectangleShape,4> m_bar;
    sf::Texture m_texture;
    std::array<sf::Sprite,9> m_sprite;
    sf::RenderWindow * m_window;
};


class Ai
{
public:
    Ai();
    Ai(const Mark aiPlayer);
    virtual ~Ai() {}

    /** Returns a suggested Board's field number */
    virtual int getSuggestedField(const Board & board, const Mark currPlayer) = 0;

    Mark getAiPlayer() const { return m_aiPlayer; }
    void setAiPlayer(const Mark p) { m_aiPlayer = p; }

    int getPointsAtLost() const { return m_pointsAtLost;}
    void setPointsAtLost(const int p) { m_pointsAtLost = p; }

    int getPointsAtWin() const { return m_pointsAtWin; }
    void setPointsAtWin(const int p) { m_pointsAtWin = p; }

    int getPointsAtDraw() const { return m_pointsAtDraw; }
    void setPointsAtDraw(const int p) { m_pointsAtDraw = p; }

protected:
    Mark m_aiPlayer;
    int m_pointsAtLost; // should be negative
    int m_pointsAtWin;  // should be positive
    int m_pointsAtDraw;
};

class RandomAi : public Ai
{
public:
    RandomAi();
    RandomAi(const Mark aiPlayer);

    /* Returns the best field for currPlayer by randomly detection */
    int getSuggestedField(const Board &, const Mark currPlayer);

    int getRandomRounds() const { return m_randomRounds; }
    void setRandomRounds(const int r) { m_randomRounds = r; }

private:
    /** Plays randomly an empty field. */
    void playRandomField(Board &, Mark currPlayer);

    int m_randomRounds;
};

class MinimaxAi : public Ai
{
public:
    MinimaxAi();
    MinimaxAi(const Mark aiPlayer);

    int getSuggestedField(const Board &, const Mark currPlayer);

private:
    int minimax(const Board &, const Mark currPlayer);
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

#endif // TICTACTOE_GUARD
