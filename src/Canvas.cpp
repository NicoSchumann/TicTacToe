#include "Canvas.hpp"
#include "Board.hpp"
#include <cstdlib>
#include <iostream>


Canvas::Canvas(sf::RenderWindow * window)
: m_window(window)
{
    if (!m_texture.loadFromFile("images/64x32_tictactoe.png"))
    {
        std::cerr << "Texture file couldn't loaded!";
        std::exit(EXIT_FAILURE);
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
