# Robot Cleaner

### 问题提出

扫地机器人(`Robot Cleaner`),又称自动打扫机、智能吸尘器等。能凭借一定的人工智能,自动在房间内完成地板清理工作。`Bosch`公司是领先的扫地机器人制造商。`Bosch`的工程师研发了一款机器人,它接受远端遥感指令, 并完成一些简单的动作。

为了方便控制机器人的导航,工程师使用三元组`(x, y, d)`来表示机器人的位置信息;其中`(x,y)`表示机器人的坐标位置,`d`表示机器人的方向 (包括`East`, `South`, `West`, `North`四个方向)。

假设机器人初始位置为`(0, 0, N)`, 表示机器人处在原点坐标、并朝向北。


## TurnTo

### 需求

- 当`Robot`收到`LEFT`指令后, `Robot`向左转`90`度;
- 当`Robot`收到`RIGHT`指令后, `Robot`向右转`90`度;

例如:

- `Robot`原来在`(0, 0, N)`, 执行`LEFT`指令后,新的位置在`(0, 0, W)`;
- `Robot`原来在`(0, 0, N)`, 执行`RIGHT`指令后,新的位置在`(0, 0, E)`。

## MoveTo

### 需求

- 当`Robot`收到`FORWARD`指令后, `Robot`保持方向, 并向前移动一个坐标;
- 当`Robot`收到`BACKWARD`指令后, `Robot`保持方向, 并向后移动一个坐标;

## Round

### 需求

当`Robot`收到`ROUND`指令后, `Robot``顺时针旋转`180`度掉头; 例`如`Robot`原来在`(0, 0, N)`,执行`ROUND`指令后,新的位置在 `(0, 0, S)`;

## MoveTo(n)

### 需求

- 当`Robot`收到`FORWARD(n)`指令后, `Robot`保持方向,向前移动`n`个坐标; 
- 当`Robot`收到`BACKWARD(n)`指令后, `Robot`保持方向,向后移动`n`个坐标; 
- 其中`n`在`[1..10]`之间;

例如:

-`Robot`原来在`(0, 0, N)`,执行`FORWARD(10)`指令后,新的位置在`(0, 10, N)`;
-`Robot`原来在`(0, 0, N)`,执行`BACKWARD(10)`指令后,新的位置在`(0, -10, N)`;

## Sequential

### 需求

当`Robot`收到一系列组合指令时,能够依次按指令完成相应的动作。例如收到指令序列:`[LEFT, FORWARD, RIGHT, BACKWARD, ROUND, FORWARD(2)]`,将依次执行:向左转`90`度;保持方向并向前移动一个坐标;向右转`90`度;保持方向并向后退一个坐标;顺时针旋转`180`度掉头;保持方向向前移动`2`个坐标。

## Repeat

### 需求

当`Robot`收到`REAPT(instruction, n)`指令后,它会循环执行`instruction`指令`n`次。原来在`(0, 0, N)`, 执行 `REAPT(FORWARD(2), 2)`指令后, 新的位置为`(0, 4, NORTH)`; 其中`n`在`[1..10]`之间。


