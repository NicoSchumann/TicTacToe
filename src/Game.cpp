#include "Game.hpp"
#include "Ai.hpp"
#include "Board.hpp"
#include <memory>
    
Game::Game()
: m_currPlayer(Mark::cross)
, m_state(State::inProgress)
, m_boardPosNo(-1)
, m_done(false)
, m_aiPlayer(Mark::ring)
{
    m_canvas = std::make_unique<Canvas>();
    m_canvas->setGameHandle(this);
 
    m_ai = std::make_unique<MinimaxAi>(m_aiPlayer);

}

Game::~Game()
{}

void
Game::setDone() 
{ 
    m_done = true; 
}

void
Game::handleInput()
{
    m_canvas->handleInput();
}
/*
    // checks if AI is at draw and set AI's suggestion
    if (m_state == State::inProgress
            && m_currPlayer == m_aiPlayer
            && m_ai != nullptr
    )
    {
        m_boardPosNo = m_ai->getSuggestedField(m_board, m_currPlayer);
        return;
    }

    sf::Event event;
    m_canvas->waitEvent(event);
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
                m_boardPosNo = getButtonNo(event.mouseButton.x, event.mouseButton.y);
            }
        }
    }
}
*/

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
        m_canvas->close();
        return;
    }
    if (m_boardPosNo == -1)
    {
        return;
    }
    if (m_state != State::inProgress)
    {
        return;
    }
    if (m_board.getMark(m_boardPosNo) != Mark::empty)
    {
        std::cerr << "Game::update: m_board(m_currButtonNo) is not empty!\n";
        return;
    }


    if (m_currPlayer == Mark::cross)
    {
        m_board.setMark(Mark::cross, m_boardPosNo);
    }
    else if (m_currPlayer == Mark::ring)
    {
        m_board.setMark(Mark::ring, m_boardPosNo);
    }

    toggleCurrPlayer();

    m_boardPosNo = -1;
    m_canvas->update(m_board);
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
    m_canvas->update(m_board);
    m_canvas->render();
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
Game::receive( int msg )
{
    std::cerr << msg;
}

void 
Game::bye() {
    std::cout << "bye..\n";
}

State 
Game::getState() const
{
    return m_state;
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
        m_canvas->run();
    }
    bye();
}

