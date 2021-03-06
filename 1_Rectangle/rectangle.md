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



## refactor：知识显性化

首先魔鬼数字100并没有体现出精确到小数点后**两位**这一知识。在这里我们需要将**精度**这一知识显性化。

```C++
Rectangle::Rectangle(double width, double height)
{
    const unsigned int PRECISION = 2;
    double factor = pow(10, PRECISION);
    m_width = (unsigned int)(width * factor)/factor;
    m_height = (unsigned int)(height * factor)/factor;
}

double Rectangle::area() const
{
    const unsigned int PRECISION = 2;
    double factor = pow(10, PRECISION);
    return (unsigned int)((m_height * m_width)*factor + 0.5)/factor;
}
```

在sprint2中提及到：

长和宽的精度保持为0.01,且不按照四舍五入，例如1.236 => 1.23。

这其实就是**向下取整**，当前实现中使用了强制类型转换来达到同样的效果，但是没有直接体现出**向下取整**这一知识。在这里我们直接使用库函数floor来以明确：

```c++
Rectangle::Rectangle(double width, double height)
{
    const unsigned int PRECISION = 2;
    double factor = pow(10, PRECISION);
    m_width = floor(width * factor)/factor;
    m_height = floor(height * factor)/factor;
}

double Rectangle::area() const
{
    const unsigned int PRECISION = 2;
    double factor = pow(10, PRECISION);
    return floor((m_height * m_width)*factor + 0.5)/factor;
}
```

## refactor：去除重复

现在代码比之前的清楚多了，但是仍然存在重复，接下来我们消除重复的代码：

```c++

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
```



## sprint3:

(1)宽的取值范围为(0,100],高的取值范围为(0,75)。当值不在这个范围内，则认为矩形非法;

(2)非法的矩形的面积和周长为0;

按照需求设计出测试用例：

```c++
TEST("should calc rectangle width & height range succ")
{
    Rectangle rec(100 , 75);
    ASSERT_THAT(rec.getWidth(), eq(100));
    ASSERT_THAT(rec.getHeight(), eq(0));
    ASSERT_THAT(rec.area(), eq(0));
    ASSERT_THAT(rec.perimeter(), eq(0));
}
```

按照需求快速实现：

```c++
namespace
{
    const double MIN_WIDTH = 0;
    const double MAX_WIDTH = 100;
    const double MIN_HEIGHT = 0;
    const double MAX_HEIGHT = 75;
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
```


## refactor：去除重复

从上述代码中可以看出，计算长方形长、宽的逻辑基本一致：

如果长（宽）在取值范围内，那么则取对应的值为最终结果，否在最终结果为0。

唯一存在差异的地方是长方形的长、宽对合法取值范围的定义是不一样的。

我们这里可以提取出一个**inRange**的概念，这是个相对稳定的概念，而**getResult**依赖于这个稳定的概念，这样下来代码是稳定的。`Width`和`Height`对于**inRange**这个概念的实现都有自己的定义。

```c++
namespace
{
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
        // 对Value类的接口存在隐式约束：必须实现inRange，否在编译失败。
        return Value(value).inRange() ? processPrecision(value, 2, 0): 0;
    }
}

Rectangle::Rectangle(double width, double height)
{
    m_width = getResult<Width>(width);
    m_height = getResult<Height>(height);
}
```

## refactor：分离精度算法

精度算法是比较常用的，如果将其分离出去，能够提高函数的可重用性：

```c++
//util.h
#ifndef H44DCD35C_F5D5_4801_8E16_AF7DB6641C5A
#define H44DCD35C_F5D5_4801_8E16_AF7DB6641C5A

double floor(double value, const unsigned int precision);
double round(double value, const unsigned int precison);

#endif /* H44DCD35C_F5D5_4801_8E16_AF7DB6641C5A */

//util.cpp
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
// Rectangle.cpp 对应调用的地方修改为：
template<typename Value>
double getResult(double value)
{
    return Value(value).inRange() ? floor(value, 2): 0;
}

double Rectangle::area() const
{
    return round(getHeight() * getWidth(), 2);
}
```

这里除了对精度算法进行了分离，还对`processPrecision(value, precision, 0)`及`processPrecision(value, precision, 0.5)`进行了封装，这样做的好处有：
1. `floor`和`round`较好地表达了向下取整、四舍五入的语义。

2. 降低客户端调用的心智包袱。

## 杜绝潜规则：

在上节，我们将非法的长度、宽度的值设置为0，需求里也没有具体提及到可以这样处理。所以我们不应该投机取巧(不要将非法长度设为0)，把偶然当必然(非本质的关系不稳定)。我们做如下修改：

```c++
namespace
{
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
```

# 总结：
至此，第一个Code Kata结束了，我们回顾下我们解题的**姿势**：

1. 在拿到需求后，首先要做的是按照需求设计出测试用例。

2. 保证测试用例的正确性后，开始实现功能。

3. 测试用例通过后，意味着在当前的测试覆盖下，功能实现是正确的。

4. 改善代码的设计，**每做一次改动记得运行下测试用例**，一旦有用例失败意味着重构出现了问题，需要及时回退代码，回到上次所有用例通过的现场。

我们解题的**姿势**其实就是之前提到过的TDD基本流程：红，绿，重构。在之前的连载里，没有强调**每做一次改动记得运行下测试用例**，实属疏忽，在总结里面做下强调。



此次Code Kata我们主要对代码去除了重复，并且在代码的表现力、语义方面进行了改善。关于**重构**可以参考《*重构*：*改善既有代码的设计*》一书。



**实践才能出真知，很多东西仍需要在练习的过程中去体会。**

附上整个工程的地址：[Kata Rectangle](https://github.com/yanxicheung/Kata/tree/main/1_Rectangle)

