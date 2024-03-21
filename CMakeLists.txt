cmake_minimum_required(VERSION 3.24)
project(untitled42)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled42 drawingModule.cpp ImageProcessing.cpp Image.cpp Size.cpp Rectangle.cpp Main.cpp Point.cpp)
