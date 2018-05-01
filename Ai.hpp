#ifndef AI_GUARD
#define AI_GUARD

#include "Board.hpp"

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

#endif // AI_GUARD
