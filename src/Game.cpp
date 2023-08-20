#include "Game.hpp"
#include "Ai.hpp"
#include "Board.hpp"
#include <memory>
    
Game::Game(sf::RenderWindow * window)
: m_window(window)
, m_canvas(window)
, m_currPlayer(Mark::cross)
, m_state(State::inProgress)
, m_currButtonNo(-1)
, m_done(false)
, m_aiPlayer(Mark::ring)
{
    m_ai = std::make_unique<MinimaxAi>(m_aiPlayer);
    resize();
}
Game::Game()
: Game(new sf::RenderWindow(sf::VideoMode(300,300),"TicTacToe"))
{}
Game::~Game()
{
    delete m_window;
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
                std::cerr << "Game::reset()"; // debug
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
        std::cerr << "Game::update: m_board(m_currButtonNo) is not empty!\n";
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
    // std::cerr << m_board << '\n'; // debug
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
    std::cout << "Hint:\nReset the board with a right-click on the board.\n";
}

void
Game::setRandomAI()
{
    m_ai.reset(new RandomAi());
}
void
Game::setMinimaxAI()
{
    m_ai.reset(new MinimaxAi());
}
void
Game::setNoAI()
{
    m_ai.reset(nullptr);
    m_aiPlayer = Mark::empty;
}
void
Game::setAIPlayer(const Mark aiPlayer)
{
    m_aiPlayer = aiPlayer;
}

void 
Game::bye() {
    std::cout << "bye..\n";
}
void
Game::run()
{
    setMinimaxAI();  // chose your A.I.
    //game.setRandomAI();
    // game.setNoAI()

    intro();

    while(!isDone())
    {
        render();
        handleInput();
        update();
    }
    bye();
}

