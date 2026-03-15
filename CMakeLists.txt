cmake_minimum_required(VERSION 3.10)

project(RigidBody2D-GL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(RigidBody2D-GL
    src/app/main.cpp
    src/physics/ball.cpp
    src/physics/world.cpp
)

target_include_directories(RigidBody2D-GL PRIVATE
    include
)