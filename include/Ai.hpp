#ifndef AI_GUARD_HPP
#define AI_GUARD_HPP

class Board;
enum class Mark;

class Ai
{
public:
    Ai();
    Ai(const Mark aiPlayer);
    virtual ~Ai() {}

    /** Returns the best playable field number.
     * @returns -1 if the board couln't  evaluated.
     * Field number range is from 0 to 8.
     */
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
    Mark m_aiPlayer;    // Mark::empty means no AI player
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
    virtual int getSuggestedField(const Board &, const Mark currPlayer) override;

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

    virtual int getSuggestedField(const Board &, const Mark currPlayer) override;

private:
    int minimax(const Board &, const Mark currPlayer);
};

#endif // AI_GUARD_HPP
