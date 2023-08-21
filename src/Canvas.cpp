#include "Canvas.hpp"
#include "Board.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include "Game.hpp"

Canvas::Canvas()
{
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(300, 300), "Reset by R-click.");

    if (!m_texture.loadFromFile("images/64x32_tictactoe.png"))
    {
        std::cerr << "Texture file couldn't loaded!";
        std::exit(EXIT_FAILURE);
    }
    for (auto &sprite : m_sprites)
    {
        sprite = sf::Sprite(m_texture, sf::Rect<int>(64, 0, 32, 32));
        sprite.setOrigin(16, 16);
    }
    this->initialize();
}

Canvas::~Canvas()
{
}

void Canvas::initialize()
{
    sf::Vector2u wSize = m_window->getSize();

    // Adjust the bars:
    for (std::size_t i = 0; i < m_bars.size(); ++i)
    {
        m_bars[i].setFillColor(sf::Color(0xaa, 0xbb, 0xcc));

        if (i % 2 == 0) // 0, 2; horizontal bars
        {
            m_bars[i].setOrigin(0, 2);
            m_bars[i].setSize(sf::Vector2<float>(wSize.x, 5));
            if (i == 0)
            {
                m_bars[i].setPosition(0, wSize.y / 3);
            }
            else
            {
                m_bars[i].setPosition(0, 2 * wSize.y / 3);
            }
        }
        else // 1, 3; vertical bars
        {
            m_bars[i].setOrigin(2, 0);
            m_bars[i].setSize(sf::Vector2<float>(5, wSize.y));
            if (i == 1)
            {
                m_bars[i].setPosition(wSize.x / 3, 0);
            }
            else
            {
                m_bars[i].setPosition(2 * wSize.x / 3, 0);
            }
        }
    }
    // Adjust the marks:
    m_sprites[0].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 1);
    m_sprites[1].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 1);
    m_sprites[2].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 1);
    m_sprites[3].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 3);
    m_sprites[4].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 3);
    m_sprites[5].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 3);
    m_sprites[6].setPosition(wSize.x / 6.0f * 1, wSize.y / 6.0f * 5);
    m_sprites[7].setPosition(wSize.x / 6.0f * 3, wSize.y / 6.0f * 5);
    m_sprites[8].setPosition(wSize.x / 6.0f * 5, wSize.y / 6.0f * 5);
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
    for (std::size_t i = 0; i < m_buttons.size(); ++i)
    {
        if (m_buttons[i].contains(x, y))
        {
            return i;
        }
    }
    return -1; // if something goes wrong
}

void Canvas::resize()
{
    sf::Vector2<unsigned int> wSize = m_window->getSize();
    int bWidth = wSize.x / 3;
    int bHeight = wSize.y / 3;

    m_buttons[0] = sf::Rect<int>(0, 0, bWidth, bHeight);
    m_buttons[1] = sf::Rect<int>(bWidth, 0, bWidth, bHeight);
    m_buttons[2] = sf::Rect<int>(2 * bWidth, 0, bWidth, bHeight);
    m_buttons[3] = sf::Rect<int>(0, bHeight, bWidth, bHeight);
    m_buttons[4] = sf::Rect<int>(bWidth, bHeight, bWidth, bHeight);
    m_buttons[5] = sf::Rect<int>(2 * bWidth, bHeight, bWidth, bHeight);
    m_buttons[6] = sf::Rect<int>(0, 2 * bHeight, bWidth, bHeight);
    m_buttons[7] = sf::Rect<int>(bWidth, 2 * bHeight, bWidth, bHeight);
    m_buttons[8] = sf::Rect<int>(2 * bWidth, 2 * bHeight, bWidth, bHeight);
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
            else if ( event.mouseButton.button == sf::Mouse::Left)
            {
                int boardPosNo = getBoardPosNo(event.mouseButton.x, event.mouseButton.y);
                m_game->receive(boardPosNo);
            }
        }
    }
}