#include "Rectangle.h"
#include "util.h"
namespace
{
    const double MIN_WIDTH = 0;
    const double MAX_WIDTH = 100;
    const double MIN_HEIGHT = 0;
    const double MAX_HEIGHT = 75;

    struct Width
    {
        Width(double value):value(value){}
        bool isVaild() const
        {
            return value > MIN_WIDTH and value <= MAX_WIDTH;
        }
    private:
        double value;
    };

    struct Height
    {
        Height(double value):value(value){}
        bool isVaild() const
        {
            return value > MIN_HEIGHT and value < MAX_HEIGHT;
        }
     private:
         double value;
     };
}

Rectangle::Rectangle(double width, double height):
m_width(floor(width, 2)),m_height(floor(height, 2)){}

double Rectangle::area() const
{
    if(not isVaild())
        return 0;
    return round(getHeight() * getWidth(), 2);
}

double Rectangle::perimeter() const
{
    if(not isVaild())
        return 0;
    return 2 * (getHeight() + getWidth());
}

bool Rectangle::isVaild() const
{
    return Width(m_width).isVaild() and Height(m_height).isVaild();
}
