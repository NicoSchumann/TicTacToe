#include "Tictactoe.hpp"
#include <iostream> // for debugging


/*-------- helping functions ----------*/

/** Overloads the << operator, so that enum Mark objects could be printed */
std::ostream& operator<<(std::ostream& o, Mark m)
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
/** Overloads the << operator, so that Board objects could be printed */
std::ostream & operator<<(std::ostream& ostr, const Board& board)
{
    ostr << '\n';
    for (int i = 0; i < 9; ++i)
    {
        Mark mark = board.getMark(i);
        if (mark == Mark::cross) ostr << 'x';
        else if (mark == Mark::ring) ostr << 'o';
        else ostr << ' ';
        if (i == 2 || i == 5 || i == 8) ostr << '\n';
    }
    return ostr;
}

/*------- class Board ------*/
Board::Board()
{
    reset();
}
Board::~Board()
{}
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
Board::getMark(int position) const
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
        std::cerr << " winner:cross ";  // debug
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
        std::cerr << " winner:ring "; // debug
        return State::ring;
    }

    // Check if game is still in progress.
    // That's if any field is empty.
    for (auto & field : m_fields)
    {
        if (field == Mark::empty)
        {
            std::cerr << " winner:inProgess ";  // debug
            return State::inProgress;
        }
    }

    // No winner, not in progress, so it must be a draw.
    std::cerr << " winner:draw ";  // debug
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
        sprite = sf::Sprite(m_texture, sf::Rect<int>(64,0,32,32)); // should later be (64,0,32,32)
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
Canvas::update(Board & board)
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
    //std::cerr << " canvasupdate "; // debug
}

/*--------- class Game -------*/
Game::Game(sf::RenderWindow * window)
: m_window(window)
, m_canvas(window)
, m_currPlayer(Mark::cross)
, m_state(State::inProgress)
, m_currButtonNo(-1)
, m_done(false)
, m_kiPlayer(Mark::empty)
, m_ki(nullptr)
{
    resize();
}
Game::Game()
: Game(new sf::RenderWindow(sf::VideoMode(300,300),"TicTacToe"))
{}
Game::~Game()
{
    delete m_window;
    if (m_ki != nullptr) { delete m_ki; }
}

void
Game::handleInput()
{
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
        else if (m_currPlayer == m_kiPlayer && m_ki != nullptr){
            m_currButtonNo = m_ki->getButtonNo();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
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
Game::getButtonNo(int x, int y) const
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
    if (m_board.getMark(m_currButtonNo) == Mark::empty)
    {
        if (m_currPlayer == Mark::cross)
        {
            m_board.setMark(Mark::cross, m_currButtonNo);
            // debug
            //std::cerr << "m_currButtonNo:" << m_currButtonNo
            //        << " boardsMark:" << m_board.getMark(m_currButtonNo)
            //        << '\n';
        }
        else if (m_currPlayer == Mark::ring)
        {
            m_board.setMark(Mark::ring, m_currButtonNo);
            // debug
            //std::cerr << "m_currButtonNo:" << m_currButtonNo
            //        << " boardsMark:" << m_board.getMark(m_currButtonNo)
            //        << '\n';
        }
        toggleCurrPlayer();
    }
    // std::cerr << " m_currButtonNo:" << m_currButtonNo << '\n';  // debug
    m_currButtonNo = -1;
    m_canvas.update(m_board);
    std::cerr << m_board; // debug
    m_state = m_board.evaluate();

}
bool
Game::isDone() const
{
    return m_done;
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

/*------------- class Ki --------------*/
int
Ki::getButtonNo()
{
    // not yet implemented
}

