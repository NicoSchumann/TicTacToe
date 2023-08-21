#include "Game.hpp"
#include "Ai.hpp"
#include "Board.hpp"
#include <memory>
#include <future>

Game::Game()
    : m_currPlayer(Mark::cross), m_state(State::inProgress), m_aiState(AIState::playerA)
{
    m_canvas = std::make_unique<Canvas>();
    // connecting m_canvas to this object
    m_canvas->setGameHandle(this);

    m_ai = std::make_unique<MinimaxAi>();
}

Game::~Game()
{
}

void Game::run()
{
    if (m_aiState == AIState::both)
    {
        while (m_state == State::inProgress)
        {
            processAI(); // Canvas will automatically updated.
            toggleCurrPlayer();
        }
    }
    else
    {
        m_canvas->run(); // This is teh main loop
    }
}

void Game::receive(const int boardFieldNo)
{
    // We check if game is still in progress
    // and the board field is still emty.
    // If so, the board will updated.
    if (
        (m_state == State::inProgress &&
         m_board.getMark(boardFieldNo) == Mark::empty) == false)
    {
        return;
    }
    // updates the board
    m_board.setMark(m_currPlayer, boardFieldNo);
    m_state = m_board.evaluate();

    // updates the canvas
    m_canvas->receive(m_currPlayer, boardFieldNo);

    if (m_aiState == AIState::playerA || m_aiState == AIState::playerB)
    {
        toggleCurrPlayer();
        processAI();
        toggleCurrPlayer();
    }
}

void Game::toggleCurrPlayer()
{
    m_currPlayer = (m_currPlayer == Mark::ring ? Mark::cross : Mark::ring);
}

void Game::reset()
{
    m_board.reset();
    m_state = State::inProgress;
    m_canvas->update(m_board);
}

void Game::setRandomAI()
{
    m_ai.reset(new RandomAi());
}
void Game::setMinimaxAI()
{
    m_ai.reset(new MinimaxAi());
}
void Game::setNoAI()
{
    m_ai.reset(nullptr);
}
void Game::setAIState(const AIState state)
{
    m_aiState = state;
}

void Game::processAI()
{
    int field = m_ai->getSuggestedField(m_board, m_currPlayer);   
    if (field != -1)
    {
        m_board.setMark(m_currPlayer, field);
        m_state = m_board.evaluate();
        m_canvas->receive(m_currPlayer, field);
    }
}