#include "Rectangle.h"
#include <cmath>

namespace
{
    const double MIN_WIDTH = 0;
    const double MAX_WIDTH = 100;
    const double MIN_HEIGHT = 0;
    const double MAX_HEIGHT = 75;

    double processPrecision(double value, const unsigned int precision, double compensation)
    {
        double factor = pow(10, precision);
        return floor(value * factor + compensation)/factor;
    }
}

Rectangle::Rectangle(double width, double height)
{
    double m_width_result = processPrecision(width, 2, 0);
    if(m_width_result > MIN_WIDTH and m_width_result <= MAX_WIDTH) m_width = m_width_result;
    else m_width = 0;

    double m_height_result = processPrecision(height, 2, 0);
    if(m_height_result > MIN_HEIGHT and m_height_result < MAX_HEIGHT) m_height = m_height_result;
    else m_height = 0;
}

double Rectangle::area() const
{
    return processPrecision(getHeight() * getWidth(), 2, 0.5);
}

double Rectangle::perimeter() const
{
    if(getHeight() == 0 or getWidth() == 0)
        return 0;
    return 2 * (getHeight() + getWidth());
}
