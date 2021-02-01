# TDD：

​		TDD是测试驱动开发的简称，是一种增量式软件开发技术，简单来说即使在没有失败的单元测试的前提下不可以写产品代码。这些测试要很小，而且要自动化。



Bob大叔用三个简单的法则来描述（约束）测试驱动开发：

1. 除非是让一个失败的单元测试通过，否在不要写产品代码。（靠测试驱动来写产品代码）
2. 不要写比足以失败更多的单元测试，构建失败也可以。（最多只有一个失败的单元测试用例）
3. 不要写比足以让单元测试通过更多的产品代码。（奔着单元测试写最小实现）

<img src="/home/daniel/workbench/workspace/写作/Kata/0_TDD/tdd.png" style="zoom:80%;" />

TDD 的基本流程是：红，绿，重构。更详细的流程是：

- 写一个测试用例
- 运行测试
- 写刚好能让测试通过的实现
- 运行测试
- 识别坏味道，用手法修改代码
- 运行测试



TDD难点是任务的拆分和用例的设计。文献4给出了一个示例，可以仔细看下。



# 环境搭建：

​		TDD依赖于测试自动化，所以我们需要一个自动化单元测试框架，这里我选择了cut，具体安装和使用可以查看参考文献1。

​		这里我还是使用cmake来构建整个项目，对cmake构建不熟悉的可以参考以前的文章：

[CMake Build工程模板](https://www.jianshu.com/p/341994b1e1ac)。IDE使用eclipse。工程模板参考：https://github.com/yanxicheung/Kata/tree/main/0_TDD/project



环境搭建完后，效果如图：

![](/home/daniel/workbench/workspace/写作/Kata/0_TDD/result.png)



# 未完待续：

​     在后面的文章中我会以Code Kata的形式，在面向对象设计、整洁代码、重构、测试驱动开发等方面进行刻意练习，提升基本开发能力。



# 参考文献：

1. cut源代码：https://github.com/horance-liu/cut
2. 测试驱动的嵌入式C语言开发
3. 百问TDD：https://www.jianshu.com/nb/45139575
4. 深度解读 - TDD（测试驱动开发）：https://www.jianshu.com/p/62f16cd4fef3
