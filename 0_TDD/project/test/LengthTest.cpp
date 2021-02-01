#include "cut/cut.hpp"
#include "Length.h"

USING_CUM_NS

FIXTURE(LengthTest)
{
    TEST("1 feet should equal to 12 inch")
    {
        ASSERT_THAT(Length(1, FEET), eq(Length(12, INCH)));
    }
};
