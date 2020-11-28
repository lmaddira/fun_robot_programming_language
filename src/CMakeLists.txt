cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mujin_interview)

add_executable(mujin mujin.cpp environment.h environment.cpp robot.h robot.cpp)
target_link_libraries(mujin PUBLIC)



