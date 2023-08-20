#ifndef BOARD_GUARD_HPP
#define BOARD_GUARD_HPP

#include <iostream>
#include <array>

enum class Mark { empty, cross, ring };
enum class State { inProgress, cross, ring, draw };

/** Overloads the << operator, so that the enums could be printed to console. */
std::ostream& operator<<(std::ostream &, const Mark);
std::ostream & operator<<( std::ostream &, const State);

class Board; // forward declaration

/** For printing a Board object to console */
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

#endif // BOARD_GUARD_HPP
