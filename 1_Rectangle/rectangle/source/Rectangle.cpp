#include "Rectangle.h"
#include <cmath>

namespace
{
    double processPrecision(double value, const unsigned int precision, double compensation)
    {
        double factor = pow(10, precision);
        return floor(value * factor + compensation)/factor;
    }
}


Rectangle::Rectangle(double width, double height)
{
    m_width = processPrecision(width, 2, 0);
    m_height = processPrecision(height, 2, 0);
}

double Rectangle::area() const
{
    return processPrecision(m_height * m_width, 2, 0.5);
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
