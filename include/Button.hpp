#ifndef BUTTON_HPP_GUARD
#define BUTTON_HPP_GUARD

#include <SFML/Graphics/RectangleShape.hpp>

class Canvas;

template <typename T>
class Callback
{
public:
    /** The callee could be e.g: void fnc(void *data) */
    void setCallback(T *c, void (T::*callee)());
    void press();

protected:
    void (T::*m_callee)() = nullptr;
    T *m_object = nullptr;
};

template <typename T>
class Button : public Callback<T>
{
public:
    /** If the position is inside the area */
    bool intersect(float posX, float posY);
    sf::RectangleShape &getRect();

private:
    sf::RectangleShape m_shape;
};

#include "Button.hpp"
#include "Canvas.hpp"

template <typename T>
void Callback<T>::setCallback(T *c, void (T::*callee)())
{
    m_callee = callee;
    m_object = c;
}

template <typename T>
void Callback<T>::press()
{
    (m_object->*m_callee)();
}

template <typename T>
sf::RectangleShape &
Button<T>::getRect()
{
    return m_shape;
}

template <typename T>
bool Button<T>::intersect(float x, float y)
{
    return x >= m_shape.getPosition().x &&
           y >= m_shape.getPosition().y &&
           x <= m_shape.getPosition().x + m_shape.getSize().x &&
           y <= m_shape.getPosition().y + m_shape.getSize().y;
}
#endif // BUTTON_HPP_GUARD