#include "Canvas.hpp"
#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include "Game.hpp"
#include "Button.hpp"

constexpr unsigned int BOARD_WIDTH = 300;
constexpr unsigned int BOARD_HEIGHT = 300;
constexpr unsigned int BUTTON_WIDTH = 100;
constexpr unsigned int BUTTON_HEIGHT = 30;

Canvas::Canvas()
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode((BOARD_WIDTH) + (BUTTON_WIDTH), (BOARD_HEIGHT)), "Reset by R-click.");
    m_buttonToggleAI = new Button<Canvas>();
    m_buttonToggleAIState = new Button<Canvas>();

    if (!m_texture.loadFromFile("images/64x32_tictactoe.png"))
    {
        std::cerr << "Texture file couldn't loaded!";
        std::exit(EXIT_FAILURE);
    }
    this->initialize();
}

Canvas::~Canvas()
{
    delete m_buttonToggleAI;
    delete m_buttonToggleAIState;
}


void Canvas::initialize()
{
    sf::Vector2u wSize = m_window->getSize();
    sf::Vector2f boardSize;

    // boardSize is board's size
    boardSize.x = wSize.x - BUTTON_WIDTH;
    boardSize.y = wSize.y;

    // Adjust the bars:
    for (std::size_t i = 0; i < m_bars.size(); ++i)
    {
        m_bars[i].setFillColor(sf::Color(0xaa, 0xbb, 0xcc));

        if (i % 2 == 0) // 0, 2; horizontal bars
        {
            m_bars[i].setOrigin(0, 2);
            m_bars[i].setSize(sf::Vector2<float>(boardSize.x, 5));
            if (i == 0)
            {
                m_bars[i].setPosition(0, boardSize.y / 3);
            }
            else
            {
                m_bars[i].setPosition(0, 2 * boardSize.y / 3);
            }
        }
        else // 1, 3; vertical bars
        {
            m_bars[i].setOrigin(2, 0);
            m_bars[i].setSize(sf::Vector2<float>(5, boardSize.y));
            if (i == 1)
            {
                m_bars[i].setPosition(boardSize.x / 3, 0);
            }
            else
            {
                m_bars[i].setPosition(2 * boardSize.x / 3, 0);
            }
        }
    }

       for (auto &sprite : m_sprites)
    {
        sprite = sf::Sprite(m_texture, sf::Rect<int>(64, 0, 32, 32));
        sprite.setOrigin(16, 16); // center
    }
 
    // Adjust the marks. Position is at center of sprite objects.
    m_sprites[0].setPosition(boardSize.x / 6.0f * 1, boardSize.y / 6.0f * 1);
    m_sprites[1].setPosition(boardSize.x / 6.0f * 3, boardSize.y / 6.0f * 1);
    m_sprites[2].setPosition(boardSize.x / 6.0f * 5, boardSize.y / 6.0f * 1);
    m_sprites[3].setPosition(boardSize.x / 6.0f * 1, boardSize.y / 6.0f * 3);
    m_sprites[4].setPosition(boardSize.x / 6.0f * 3, boardSize.y / 6.0f * 3);
    m_sprites[5].setPosition(boardSize.x / 6.0f * 5, boardSize.y / 6.0f * 3);
    m_sprites[6].setPosition(boardSize.x / 6.0f * 1, boardSize.y / 6.0f * 5);
    m_sprites[7].setPosition(boardSize.x / 6.0f * 3, boardSize.y / 6.0f * 5);
    m_sprites[8].setPosition(boardSize.x / 6.0f * 5, boardSize.y / 6.0f * 5);
    
    wSize = m_window->getSize();

    // boardSize is board's size
    boardSize.x = wSize.x - BUTTON_WIDTH;
    boardSize.y = wSize.y;


 
    sf::Vector2f buttonSize = sf::Vector2f(static_cast<float>(wSize.x) - boardSize.x, static_cast<float>(BUTTON_HEIGHT));
 
    m_buttonToggleAI->getRect().setOrigin(sf::Vector2f(0.f, 0.f));
    m_buttonToggleAI->getRect().setSize(buttonSize);
    m_buttonToggleAI->getRect().setPosition(sf::Vector2f(boardSize.x, 0.f));
    m_buttonToggleAI->getRect().setFillColor(sf::Color::Blue);
    m_buttonToggleAI->getRect().setOutlineColor(sf::Color::Red);
    m_buttonToggleAI->getRect().setOutlineThickness(-5.f);
    m_buttonToggleAI->setCallback(this, &Canvas::toggleAI);

    m_buttonToggleAIState->getRect().setOrigin(sf::Vector2f(0.f, 0.f));
    m_buttonToggleAIState->getRect().setSize(buttonSize);
    m_buttonToggleAIState->getRect().setPosition(sf::Vector2f(boardSize.x, static_cast<float>(BUTTON_HEIGHT)));
    m_buttonToggleAIState->getRect().setFillColor(sf::Color::Blue);
    m_buttonToggleAIState->getRect().setOutlineColor(sf::Color::Red);
    m_buttonToggleAIState->getRect().setOutlineThickness(-5.f);
    m_buttonToggleAIState->setCallback(this, &Canvas::toggleAIState);

    sf::RectangleShape r = m_buttonToggleAI->getRect();
    sf::Vector2f o = r.getOrigin();
    sf::Vector2f pos = r.getPosition();
    sf::Vector2f sz = r.getSize();
    std::cerr <<o.x<<','<<o.y<<'|'<<pos.x<<','<<pos.y<<'|'<<sz.x<<','<<sz.y<<'\n';

}

void Canvas::render()
{
    m_window->clear(sf::Color::Black);

    for (auto bar : m_bars)
    {
        m_window->draw(bar);
    }
    for (auto &sprite : m_sprites)
    {
        m_window->draw(sprite);
    }

    sf::RectangleShape r = m_buttonToggleAI->getRect();
    sf::Vector2f o = r.getOrigin();
    sf::Vector2f pos = r.getPosition();
    sf::Vector2f sz = r.getSize();
    std::cerr <<o.x<<','<<o.y<<'|'<<pos.x<<','<<pos.y<<'|'<<sz.x<<','<<sz.y<<'\n';

    m_window->draw(m_buttonToggleAI->getRect());
    m_window->draw(m_buttonToggleAIState->getRect());
    m_window->display();
}

void Canvas::update(const Board &board)
{
    for (int i = 0; i < 9; ++i)
    {
        Mark mark = board.getMark(i);
        switch (mark)
        {
        case Mark::cross:
            m_sprites[i].setTextureRect(sf::Rect<int>(0, 0, 32, 32));
            break;
        case Mark::ring:
            m_sprites[i].setTextureRect(sf::Rect<int>(32, 0, 32, 32));
            break;
        default:
            m_sprites[i].setTextureRect(sf::Rect<int>(64, 0, 32, 32));
        }
    }
}

void Canvas::close()
{
    m_window->close();
}

int Canvas::getBoardPosNo(const int x, const int y) const
{
    for (std::size_t i = 0; i < m_fields.size(); ++i)
    {
        if (m_fields[i].contains(x, y))
        {
            return i;
        }
    }
    return -1; // if something goes wrong
}

void Canvas::resize()
{
    sf::Vector2u winSize = m_window->getSize();
    float bWidth = (winSize.x - BUTTON_WIDTH) / 3;
    float bHeight = winSize.y / 3;

    m_fields[0] = sf::Rect<int>(0, 0, bWidth, bHeight);
    m_fields[1] = sf::Rect<int>(bWidth, 0, bWidth, bHeight);
    m_fields[2] = sf::Rect<int>(2 * bWidth, 0, bWidth, bHeight);
    m_fields[3] = sf::Rect<int>(0, bHeight, bWidth, bHeight);
    m_fields[4] = sf::Rect<int>(bWidth, bHeight, bWidth, bHeight);
    m_fields[5] = sf::Rect<int>(2 * bWidth, bHeight, bWidth, bHeight);
    m_fields[6] = sf::Rect<int>(0, 2 * bHeight, bWidth, bHeight);
    m_fields[7] = sf::Rect<int>(bWidth, 2 * bHeight, bWidth, bHeight);
    m_fields[8] = sf::Rect<int>(2 * bWidth, 2 * bHeight, bWidth, bHeight);

    m_buttonToggleAI->getRect().setPosition(sf::Vector2f(static_cast<float>(winSize.x) - static_cast<float>(BUTTON_WIDTH), 0.f));
    m_buttonToggleAIState->getRect().setPosition(sf::Vector2f(static_cast<float>(winSize.x) - static_cast<float>(BUTTON_WIDTH), static_cast<float>(BUTTON_HEIGHT)));
}

void Canvas::setGameHandle(Game *game)
{
    m_game = game;
}

void Canvas::receive(Mark mark, int boardField)
{
    // TODO: Here should the sprite array been
    // updaded.
    switch (mark)
    {
    case Mark::cross:
        m_sprites[boardField].setTextureRect(sf::Rect<int>(0, 0, 32, 32));
        break;
    case Mark::ring:
        m_sprites[boardField].setTextureRect(sf::Rect<int>(32, 0, 32, 32));
        break;
    default:
        m_sprites[boardField].setTextureRect(sf::Rect<int>(64, 0, 32, 32));
    }
}

void Canvas::toggleAI()
{
    m_game->toggleAI();
}

void Canvas::toggleAIState()
{
    m_game->toggleAIState();
}

void Canvas::run()
{
    this->handleInput();
}

void Canvas::handleInput()
{
    sf::Event event;
    while (m_window->isOpen())
    {
        this->render();

        m_window->waitEvent(event);

        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
        else if (event.type == sf::Event::Resized)
        {
            this->resize();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                m_game->reset();
                this->render();
                // std::cerr << "Game::reset()"; // debug
            }
            else if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f pos(event.mouseButton.x, event.mouseButton.y);
                if( m_buttonToggleAI->intersect(pos.x, pos.y))
                {
                    m_buttonToggleAI->press();
                    continue;
                }
                else if( m_buttonToggleAIState->intersect(pos.x, pos.y))
                {
                    m_buttonToggleAIState->press();
                    continue;
                }
                else
                {
                    int boardPosNo = getBoardPosNo(pos.x, pos.y);
                    m_game->receive(boardPosNo);
                }

            }
        }
    }
}