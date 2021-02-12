#include <cmath>
#include "util.h"
namespace
{
    double processPrecision(double value, const unsigned int precision, double compensation)
    {
        double factor = ::pow(10, precision);
        return ::floor(value * factor + compensation)/factor;
    }
}

double floor(double value, const unsigned int precision)
{
    return processPrecision(value, precision, 0);
}

double round(double value, const unsigned int precision)
{
    return processPrecision(value, precision, 0.5);
}

