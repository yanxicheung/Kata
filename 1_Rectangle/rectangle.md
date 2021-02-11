# rectangle

## sprint1:

(1)计算矩形面积和周长;

先写出测试用例：

```c++
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
};
```

很简单，步子可以垮的大些，我们直接实现：

```c++
Rectangle::Rectangle(unsigned int width, unsigned int height):
m_width(width), m_height(height){}

unsigned int Rectangle::area() const
{
    return m_height * m_width;
}

unsigned int Rectangle::perimeter() const
{
    return 2 * (m_height + m_width);
}
```



## sprint2:

(1)长和宽的精度保持为0.01,且不按照四舍五入，例如1.236 => 1.23

(2)面积精度保持为0.01,且按照四舍五入，例如1.236 => 1.24

我们先按照需求先写出单元测试：

```C++
  TEST("should calc rectangle width& height succ")
    {
        Rectangle rec(10.123 , 2.346);
        ASSERT_THAT(rec.getWidth(), eq(10.12));
        ASSERT_THAT(rec.getHeight(), eq(2.34));
    }
```

先给出一个伪实现，快速通过测试用例：

```c++
double Rectangle::getWidth() const
{
    return 10.12;
}

double Rectangle::getHeight() const
{
    return 2.34;
}
```

这步看样子有点多余，其实是用二分查找法隔离问题，通过 hardcode 实现通过测试后，就基本确定测试是没有问题，这时再去实现产品代码，如果测试不通过，就是产品代码的问题。所以小步快走主要是为了隔离问题，也就是你可以告别 Debug 了。



基于正确的测试用例，我们现在给出一个快速实现的版本：

```c++
Rectangle::Rectangle(double width, double height)
{
    m_width = (unsigned int)(width * 100)/100.0;
    m_height = (unsigned int)(height * 100)/100.0;
}

double Rectangle::getWidth() const
{
    return m_width;
}

double Rectangle::getHeight() const
{
    return m_height;
}
```

继续添加单元测试，这次要考虑到面积，面积的精度要精确到小数点后两位，同时满足四舍五入：

```c++
    TEST("should calc rectangle width& height &area succ")
    {
        Rectangle rec(10.123 , 2.346);
        ASSERT_THAT(rec.getWidth(), eq(10.12));
        ASSERT_THAT(rec.getHeight(), eq(2.34));
        ASSERT_THAT(rec.area(), eq(23.68));
    }
```

给出一个快速实现的版本：

```c++
double Rectangle::area() const
{
    return (unsigned int)((m_height * m_width)*100 + 0.5)/100.0;
}
```


从实现代码来看,每个函数的有效代码都不超过3行。现实项目的代码如果能够被控制在这样的复杂度,维护成本就不会是个大问题。但,这份实现真的没有任何问题吗?



可以看出在当前代码中存在大量的魔鬼数字（magic  number）,同时矩形的长度、宽度、面积精度的算法存在重复，在下一篇文章中我们将基于上述问题，对代码进行重构，以此来改善代码的设计。



## sprint3:

(1)宽的取值范围为(0,100],高的取值范围为(0,75)。当值不在这个范围内，则认为矩形非法;

(2)非法的矩形的面积和周长为0;



## sprint4:

(1)计算正方形的周长和面积;

(2)边长保持精度为0.01,且不进行四舍五入，例如1.236 => 1.23

(3)边长的取值范围为(0，75）.当值不在这个范围内，则认为正方形非法;非法的正方形的面积和周长为0;