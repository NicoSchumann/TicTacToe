#define FILE_EXCLUDER
#ifndef FILE_EXCLUDER

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

#endif