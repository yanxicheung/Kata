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
        bool inRange() const
        {
            return value > MIN_WIDTH and value <= MAX_WIDTH;
        }
    private:
        double value;
    };

    struct Height
    {
        Height(double value):value(value){}
        bool inRange() const
        {
            return value > MIN_HEIGHT and value < MAX_HEIGHT;
        }
     private:
         double value;
     };

    template<typename Value>
    double getResult(double value)
    {
        return Value(value).inRange() ? floor(value, 2): 0;
    }
}

Rectangle::Rectangle(double width, double height)
{
    m_width = getResult<Width>(width);
    m_height = getResult<Height>(height);
}

double Rectangle::area() const
{
    return round(getHeight() * getWidth(), 2);
}

double Rectangle::perimeter() const
{
    if(getHeight() == 0 or getWidth() == 0)
        return 0;
    return 2 * (getHeight() + getWidth());
}
