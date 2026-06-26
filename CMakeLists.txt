cmake_minimum_required(VERSION 3.15)

project(RigidBody2D-GL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
    GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(raylib)

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

target_link_libraries(RigidBody2D-GL PRIVATE OpenMP::OpenMP_CXX raylib)
target_link_libraries(benchmark PRIVATE OpenMP::OpenMP_CXX raylib)
