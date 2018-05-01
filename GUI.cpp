#include "GUI.hpp"

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

