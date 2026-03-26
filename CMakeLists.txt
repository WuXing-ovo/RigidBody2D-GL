cmake_minimum_required(VERSION 3.10)

project(RigidBody2D-GL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED)

add_executable(RigidBody2D-GL
    src/app/main.cpp
    src/physics/ball.cpp
    src/physics/world.cpp
)

add_executable(benchmark
    src/app/benchmark.cpp
    src/physics/ball.cpp
    src/physics/world.cpp
)

target_include_directories(RigidBody2D-GL PRIVATE
    include
)

target_include_directories(benchmark PRIVATE
    include
)

target_link_libraries(RigidBody2D-GL PRIVATE OpenMP::OpenMP_CXX)
target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX)