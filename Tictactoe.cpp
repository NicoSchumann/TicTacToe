#include "Tictactoe.hpp"
#include <climits>
#include <algorithm>


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


/*--------------- class Canvas ------------------*/

Canvas::Canvas(sf::RenderWindow * window)
: m_window(window)
{
    if (!m_texture.loadFromFile("images/64x32_tictactoe.png"))
    {
        std::cerr << "Texture file couldn't loaded!";
    }
    for (auto & sprite : m_sprite)
    {
        sprite = sf::Sprite(m_texture, sf::Rect<int>(64,0,32,32));
        sprite.setOrigin(16,16);
    }
    resize();

}

Canvas::~Canvas()
{}

void
Canvas::resize()
{
    sf::Vector2u wSize = m_window->getSize();

    // Adjust the bars:
    for (std::size_t i = 0; i < m_bar.size(); ++i)
    {
        m_bar[i].setFillColor(sf::Color(0xaa, 0xbb, 0xcc));

        if (i % 2 == 0)  // 0, 2; horizontal bars
        {
            m_bar[i].setOrigin(0, 2);
            m_bar[i].setSize(sf::Vector2<float>(wSize.x, 5));
            if (i == 0)
            {
                m_bar[i].setPosition(0, wSize.y / 3);
            }
            else
            {
                m_bar[i].setPosition(0, 2 * wSize.y / 3);
            }
        }
        else // 1, 3; vertical bars
        {
            m_bar[i].setOrigin(2, 0);
            m_bar[i].setSize(sf::Vector2<float>(5, wSize.y));
            if (i == 1)
            {
                m_bar[i].setPosition(wSize.x / 3, 0);
            }
            else
            {
                m_bar[i].setPosition(2 * wSize.x / 3, 0);
            }
        }
    }
    // Adjust the marks:
    m_sprite[0].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 1);
    m_sprite[1].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 1);
    m_sprite[2].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 1);
    m_sprite[3].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 3);
    m_sprite[4].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 3);
    m_sprite[5].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 3);
    m_sprite[6].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 5);
    m_sprite[7].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 5);
    m_sprite[8].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 5);
}

void
Canvas::render()
{
    m_window->clear(sf::Color::Black);

    for (auto bar : m_bar)
    {
        m_window->draw(bar);
    }
    for (auto & sprite : m_sprite)
    {
        m_window->draw(sprite);
    }
    m_window->display();
}

void
Canvas::update(const Board & board)
{
    for (int i = 0; i < 9; ++i)
    {
        Mark mark = board.getMark(i);
        switch (mark)
        {
        case Mark::cross:
            m_sprite[i].setTextureRect(sf::Rect<int>(0,0,32,32));
            break;
        case Mark::ring:
            m_sprite[i].setTextureRect(sf::Rect<int>(32,0,32,32));
            break;
        default:
            m_sprite[i].setTextureRect(sf::Rect<int>(64,0,32,32));
        }
    }
}


/*--------- class Game -------*/

Game::Game(sf::RenderWindow * window)
: m_window(window)
, m_canvas(window)
, m_currPlayer(Mark::cross)
, m_state(State::inProgress)
, m_currButtonNo(-1)
, m_done(false)
, m_aiPlayer(Mark::ring)
, m_ai(new MinimaxAi(m_aiPlayer))
{
    resize();
}
Game::Game()
: Game(new sf::RenderWindow(sf::VideoMode(300,300),"TicTacToe"))
{}
Game::~Game()
{
    delete m_window;
    if (m_ai != nullptr) { delete m_ai; }
}

void
Game::handleInput()
{
    // checks if AI is at draw and set AI's suggestion
    if (m_state == State::inProgress
            && m_currPlayer == m_aiPlayer
            && m_ai != nullptr
    )
    {
        m_currButtonNo = m_ai->getSuggestedField(m_board, m_currPlayer);
        return;
    }

    sf::Event event;
    m_window->waitEvent(event);
    {
        if (event.type == sf::Event::Closed)
        {
            m_done = true;
        }
        else if (event.type == sf::Event::Resized)
        {
            resize();
            // m_canvas.resize();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                reset();
                std::cerr << "hello"; // debug
            }
            else if (m_state == State::inProgress
               && event.mouseButton.button == sf::Mouse::Left
            ) {
                m_currButtonNo = getButtonNo(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}
void
Game::resize()
{
    sf::Vector2<unsigned int> wSize = m_window->getSize();
    int bWidth = wSize.x/3;
    int bHeight = wSize.y/3;

    m_button[0] = sf::Rect<int>(       0,         0, bWidth, bHeight);
    m_button[1] = sf::Rect<int>(  bWidth,         0, bWidth, bHeight);
    m_button[2] = sf::Rect<int>(2*bWidth,         0, bWidth, bHeight);
    m_button[3] = sf::Rect<int>(       0,   bHeight, bWidth, bHeight);
    m_button[4] = sf::Rect<int>(  bWidth,   bHeight, bWidth, bHeight);
    m_button[5] = sf::Rect<int>(2*bWidth,   bHeight, bWidth, bHeight);
    m_button[6] = sf::Rect<int>(       0, 2*bHeight, bWidth, bHeight);
    m_button[7] = sf::Rect<int>(  bWidth, 2*bHeight, bWidth, bHeight);
    m_button[8] = sf::Rect<int>(2*bWidth, 2*bHeight, bWidth, bHeight);
}
int
Game::getButtonNo(const int x, const int y) const
{
    for(std::size_t i = 0; i < m_button.size(); ++i)
    {
        if (m_button[i].contains(x,y))
        {
            return i;
        }
    }
    return -1; // if something goes wrong
}
Mark
Game::getCurrPlayer() const
{
    return m_currPlayer;
}
void
Game::toggleCurrPlayer()
{
    m_currPlayer = (m_currPlayer == Mark::ring? Mark::cross : Mark::ring);
}
void
Game::update()
{
    if (m_done)
    {
        m_window->close();
        delete m_window;
        return;
    }
    if (m_currButtonNo == -1)
    {
        return;
    }
    if (m_state != State::inProgress)
    {
        return;
    }
    if (m_board.getMark(m_currButtonNo) != Mark::empty)
    {
        std::cerr << "Game::update: board(m_currButtonNo is not empty!\n";
        return;
    }


    if (m_currPlayer == Mark::cross)
    {
        m_board.setMark(Mark::cross, m_currButtonNo);
    }
    else if (m_currPlayer == Mark::ring)
    {
        m_board.setMark(Mark::ring, m_currButtonNo);
    }

    toggleCurrPlayer();

    m_currButtonNo = -1;
    m_canvas.update(m_board);
    std::cerr << m_board << '\n'; // debug
    m_state = m_board.evaluate();

}
bool
Game::isDone() const
{
    return m_done;
}

void
Game::reset()
{
    m_board.reset();
    m_canvas.update(m_board);
    render();
}

void
Game::render()
{
    if (m_done) { return; }

    m_canvas.render();
}

void
Game::intro()
{
    // not yet implemented
}

void
Game::setRandomAI()
{
    if (m_ai != nullptr) delete m_ai;
    m_ai = new RandomAi;
}
void
Game::setMinimaxAI()
{
    if (m_ai != nullptr) delete m_ai;
    m_ai = new MinimaxAi;
}
void
Game::setNoAI()
{
    if (m_ai != nullptr) delete m_ai;
    m_ai = nullptr;
    m_aiPlayer = Mark::empty;
}
void
Game::setAIPlayer(const Mark aiPlayer)
{
    m_aiPlayer = aiPlayer;
}


/*------------- class Ai --------------*/

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

        Board * bo = new Board(board);
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
            Board * b = new Board(*bo);

            State state = State::inProgress;

            // play a board to its end randomly
            do {
                playRandomField( *b, cp);
                cp = (cp == Mark::cross ? Mark::ring : Mark::cross);
                state = b->evaluate();
            } while (state == State::inProgress);

            delete b; // here not longer needed

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
        // delete the board of the i-th played field
        delete bo;
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
        Board * b = new Board(board);
        b->setMark(currPlayer, i);
        int val = minimax(*b, changedPlayer );
        delete b;

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

        Board * b = new Board(board);
        b->setMark(currPlayer,i);

        int val = minimax(*b,changedPlayer);

        delete b;

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
