#include "Board.hpp"

/*-------- helping functions ----------*/

/** Overloads the << operator, so that enums could be printed to console. */
std::ostream& operator<<(std::ostream& o, const Mark m)
{
    switch (m)
    {
        case Mark::empty:
            o << "Mark::empty";
            break;
        case Mark::cross:
            o << "Mark::cross";
            break;
        case Mark::ring:
            o << "Mark::ring";
    }
    return o;
}

std::ostream & operator<<( std::ostream & o, const State s)
{
    switch (s)
    {
        case State::cross:
            o << "State::cross";
            break;
        case State::draw:
            o << "State::draw";
            break;
        case State::inProgress:
            o << "State::inProgress";
            break;
        case State::ring:
            o << "State::ring";
    }
    return o;
}

std::ostream & operator<<(std::ostream & ostr, const Board& board)
{
    for (int i = 0; i < 9; ++i)
    {
        Mark mark = board.getMark(i);
        if (mark == Mark::cross) { ostr << 'x'; }
        else if (mark == Mark::ring) { ostr << 'o'; }
        else { ostr << '-'; }
        if (i == 2 || i == 5 || i == 8) { ostr << '\n'; }
    }
    return ostr;
}

/*------- class Board ------*/
Board::Board()
{
    reset();
}
Board::Board(const Board & b)
{
    m_fields = b.m_fields;
}

void
Board::reset()
{
    for (auto & field : m_fields) field = Mark::empty;
}
void
Board::setMark(Mark mark, std::size_t position)
{
    m_fields[position] = mark;
}
Mark
Board::getMark(const int position) const
{
    return m_fields[position];
}
State
Board::evaluate() const
{
    auto & f = m_fields;

    if (  // Check for a win of player cross.
            // horizontal
        (f[0] == Mark::cross && f[0] == f[1] && f[1] == f[2])
     || (f[3] == Mark::cross && f[3] == f[4] && f[4] == f[5])
     || (f[6] == Mark::cross && f[6] == f[7] && f[7] == f[8])
            // vertical
     || (f[0] == Mark::cross && f[0] == f[3] && f[3] == f[6])
     || (f[1] == Mark::cross && f[1] == f[4] && f[4] == f[7])
     || (f[2] == Mark::cross && f[2] == f[5] && f[5] == f[8])
            // diagonal
     || (f[0] == Mark::cross && f[0] == f[4] && f[4] == f[8])
     || (f[2] == Mark::cross && f[2] == f[4] && f[4] == f[6])
    )
    {
        //std::cerr << "Cross wins.\n";  // debug
        return State::cross;
    }
    else if ( // Check for a win of player ring.
            // horizontal
        (f[0] == Mark::ring && f[0] == f[1] && f[1] == f[2])
     || (f[3] == Mark::ring && f[3] == f[4] && f[4] == f[5])
     || (f[6] == Mark::ring && f[6] == f[7] && f[7] == f[8])
            // vertical
     || (f[0] == Mark::ring && f[0] == f[3] && f[3] == f[6])
     || (f[1] == Mark::ring && f[1] == f[4] && f[4] == f[7])
     || (f[2] == Mark::ring && f[2] == f[5] && f[5] == f[8])
            // diagonal
     || (f[0] == Mark::ring && f[0] == f[4] && f[4] == f[8])
     || (f[2] == Mark::ring && f[2] == f[4] && f[4] == f[6])
    )
    {
        //std::cerr << "Ring wins.\n"; // debug
        return State::ring;
    }

    // Check if game is still in progress.
    // That's if any field is empty.
    for (auto & field : m_fields)
    {
        if (field == Mark::empty)
        {
            // std::cerr << "Game is in progess.\n";  // debug
            return State::inProgress;
        }
    }

    // No winner, not in progress, so it st be a draw.
    //std::cerr << "Game ends with a draw.\n";  // debug
    return State::draw;
}

