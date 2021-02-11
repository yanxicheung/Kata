#include "cut/cut.hpp"
#include "Rectangle.h"

USING_CUM_NS

FIXTURE(RectangleTest)
{
    TEST("should calc rectangle area succ")
    {
        Rectangle rec(10,2);
        ASSERT_THAT(rec.area(), eq(20));
    }

    TEST("should calc rectangle perimeter succ")
    {
        Rectangle rec(10,2);
        ASSERT_THAT(rec.perimeter(), eq(24));
    }


    TEST("should calc rectangle width& height succ")
    {
        Rectangle rec1(10.123 , 2.346);
        ASSERT_THAT(rec1.getWidth(), eq(10.12));
        ASSERT_THAT(rec1.getHeight(), eq(2.34));
        ASSERT_THAT(rec1.area(), eq(23.68));

        Rectangle rec2(5.234 , 1.72);
        ASSERT_THAT(rec2.getWidth(), eq(5.23));
        ASSERT_THAT(rec2.getHeight(), eq(1.72));
        ASSERT_THAT(rec2.area(), eq(9.00));  // 8.9956
    }
};
