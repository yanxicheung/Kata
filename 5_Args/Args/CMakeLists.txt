# 设置工程名称
project(rectangle) 

cmake_minimum_required(VERSION 2.8)

# 用于设置环境变量
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# 设置头文件包含路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 遍历文件
file(GLOB_RECURSE all_files
source/*.cpp
source/*.cc
source/*.c
test/*.cpp
test/*.cc
test/*.c)

# 生成目标可执行文件
add_executable(rectangle ${all_files})
target_link_libraries(rectangle cut)
