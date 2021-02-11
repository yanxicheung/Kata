#include "Rectangle.h"

Rectangle::Rectangle(double width, double height)
{
    m_width = (unsigned int)(width * 100)/100.0;
    m_height = (unsigned int)(height * 100)/100.0;
}

double Rectangle::area() const
{
    return (unsigned int)((m_height * m_width)*100 + 0.5)/100.0;
}

double Rectangle::perimeter() const
{
    return 2 * (m_height + m_width);
}

double Rectangle::getWidth() const
{
    return m_width;
}

double Rectangle::getHeight() const
{
    return m_height;
}
