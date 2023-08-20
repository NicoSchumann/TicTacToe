#include "Ai.hpp"
#include "Board.hpp"
#include <ctime>
#include <climits>
#include <memory>

/*------------- base class Ai --------------*/

Ai::Ai(Mark aiPlayer)
: m_aiPlayer(aiPlayer)
, m_pointsAtLost(-1)
, m_pointsAtWin(1)
, m_pointsAtDraw(0)
{}

Ai::Ai()
: Ai(Mark::empty)
{}


/*----- class RandomAi -----*/

RandomAi::RandomAi(const Mark aiPlayer)
: Ai::Ai(aiPlayer)
, m_randomRounds(100)
{
    std::srand(std::time(0));
}

RandomAi::RandomAi()
: RandomAi(Mark::empty)
{}


void
RandomAi::playRandomField(Board & board, Mark currPlayer)
{
    int emptyFields = 0;

    // evaluate number of empty fields of the board
    for (int i = 0; i < 9; ++i)
    {
        if (board.getMark(i) == Mark::empty)
        {
            ++ emptyFields;
        }
    }
    int r = rand() % emptyFields;

    // play the Field
    for (int i = 0; i < 9; ++i )
    {
        if (board.getMark(i) != Mark::empty)
        {
            continue;
        }
        if (r == 0)
        {
            board.setMark(currPlayer, i);
            break;
        }
        --r;
    }
}
int
RandomAi::getSuggestedField(const Board & board, const Mark currPlayer)
{
    // if the game is in finite state
    if (board.evaluate() != State::inProgress)
    {
        return -1;
    }

    std::array<int, 9> fieldVals; // holds the value of each field

    // Sets the value of non-empty fields lower than the the minimal
    // reachable points, to ensure that non-empty fields would not selected
    // at a board state where all A.I. player moves are resulting to a lost.
    // The empty fields will be initialized with 0.
    // Variable 'm_pointsAtLost' must be negative.
    for (int i = 0; i < 9; ++i)
    {
        if (board.getMark(i) == Mark::empty)
        {
            fieldVals[i] = 0;
        }
        else
        {
            // m_randomRounds must be negative
            fieldVals[i] = (m_randomRounds * m_pointsAtLost) - 1;
        }
    }

    // play with each empty field:
    for (int i = 0; i < 9; ++i)
    {
        // rejects all fields which are not empty
        if (board.getMark(i) != Mark::empty)
        {
            continue;
        }

        std::unique_ptr<Board> bo = std::make_unique<Board>(board);
        bo->setMark(currPlayer, i);

        // If playing that field results into
        // a finished board, then this could only be
        // resulted to a win for currPlayer or a draw.
        // Hence 'i' is suggested and should returned.
        if (bo->evaluate() != State::inProgress)
        {
            return i;
        }

        // play some randomly games for each free field:
        for (int k = 0; k < m_randomRounds; ++k)
        {
            // toggle player
            Mark cp = (currPlayer == Mark::cross ? Mark::ring : Mark::cross);
            // clone the board
            std::unique_ptr<Board> b = std::make_unique<Board>(*bo);

            State state = State::inProgress;

            // play a board to its end randomly
            do {
                playRandomField( *b, cp);
                cp = (cp == Mark::cross ? Mark::ring : Mark::cross);
                state = b->evaluate();
            } while (state == State::inProgress);

            // evaluate the state of the randomly played board:
            if (state == State::draw)
            {
                fieldVals[i] += m_pointsAtDraw;
            }
            else if ((state == State::cross && currPlayer == Mark::cross)
                    ||(state == State::ring && currPlayer == Mark::ring))
            {
                fieldVals[i] += m_pointsAtWin;
            }
            else  // game resulted in a lost for currPlayer
            {
                fieldVals[i] += m_pointsAtLost;
            }
        }
    }

    // evaluate the earned points
    int suggestedField = -1;
    int maxFieldVal = m_randomRounds * m_pointsAtLost -1;
    for (int i = 0; i < 9; ++i)
    {
        if (fieldVals[i] > maxFieldVal)
        {
            maxFieldVal = fieldVals[i];
            suggestedField = i;
        }
    }
    // debug
    for (int i = 0; i < fieldVals.size(); ++i)
    {
        std::cerr << "fieldVals["<<i<<"]:"<<fieldVals[i]<<"\n";
    }

    return suggestedField;
}


/*------- class MinimaxAi --------*/

MinimaxAi::MinimaxAi(const Mark aiPlayer)
: Ai::Ai(aiPlayer)
{}
MinimaxAi::MinimaxAi()
: MinimaxAi(Mark::empty)
{}

int
MinimaxAi::getSuggestedField(const Board & board, const Mark currPlayer)
{
    // if game is already finished
    if (board.evaluate() != State::inProgress)
    {
        return -1;
    }

    int fieldNo = -1;
    int fieldVal;

    if(currPlayer == Mark::cross)
    {
        fieldVal = INT_MIN;
    }
    else if (currPlayer == Mark::ring)
    {
        fieldVal = INT_MAX;
    }
    // The opponent player will be used to invoke minimax
    Mark changedPlayer = (currPlayer == Mark::cross ? Mark::ring : Mark::cross);

    // Plays the empty fields and invokes minimax() for each.
    for (int i = 0; i < 9; ++i)
    {
        if (board.getMark(i) != Mark::empty)
        {
            continue;
        }
        std::unique_ptr<Board> b = std::make_unique<Board>(board);
        b->setMark(currPlayer, i);
        int val = minimax(*b, changedPlayer );

        // Evaluates the the suggested field of the board.
        if (currPlayer == Mark::cross && val > fieldVal)
        {
            fieldVal = val;
            fieldNo = i;
        }
        else if (currPlayer == Mark::ring && val < fieldVal)
        {
            fieldVal = val;
            fieldNo = i;
        }
    }
    return fieldNo;
}

int
MinimaxAi::minimax(const Board & board, const Mark currPlayer)
{
    // Player 'cross' maximizes, player 'ring' minimizes.
    // m_pointsAtWin should be positive,
    // m_pointsAtLost should be negative.

    State state = board.evaluate();

    if (state == State::cross) return m_pointsAtWin;
    if (state == State::ring)  return m_pointsAtLost;
    if (state == State::draw)  return m_pointsAtDraw;

    int bestVal;
    if (currPlayer == Mark::cross)      bestVal = INT_MIN;
    else if (currPlayer == Mark::ring)  bestVal = INT_MAX;

    // Toggles player for invoking the minimax() with the opponent:
    Mark changedPlayer = (currPlayer == Mark::cross ? Mark::ring : Mark::cross);

    // Plays the empty fields and invoke the minimax for each.
    for (int i = 0; i < 9; ++i)
    {
        if (board.getMark(i) != Mark::empty)
        {
            continue;
        }

        std::unique_ptr<Board> b = std::make_unique<Board>(board);
        b->setMark(currPlayer,i);

        int val = minimax(*b,changedPlayer);

        // Mark::cross maximizes
        if (currPlayer == Mark::cross && val > bestVal)
        {
            bestVal = std::max(val,bestVal);
        }
        // Mark::ring minimizes
        else if (currPlayer == Mark::ring && val < bestVal)
        {
            bestVal = std::min(val,bestVal);
        }
    }
    return bestVal;
}
