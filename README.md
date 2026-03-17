# RigidBody2D-GL

## Overview

A 2D rigid body physics simulation engine with OpenGL visualization, written in C++.

Now, it's still under development.

## Current Status

Working on Stage 1, the simulated world and entities are still under development.

## Features

- CMake-based build setup
- A reasonable file structure
- Designed for future performance optimization

## Structure

```
├── include
│   └── physics
├── src
│   ├── app
│   └── physics
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Build

```
mkdir -p build
cd build
cmake ..
cmake --build .
./RigidBody2D-GL
```

## Physical Model

- Uses a fixed timestep update with gravity.
- Ball-wall and ball-ball collision handling are in progress.

## Roadmap

The whole project is divided into three stages.

- **Stage 1**: A 2D RigidBody Simulation Engine in C++
- **Stage 2**: Improve performance with OpenMP and cache optimization
- **Stage 3**: Visualization with OpenGL

## Dev Log

<details open>
<summary><b>March 2026</b></summary>

- **2026-03-17**: Redesign World class and Ball class with vec2 for easier development. Next, design a proper collision detection algorithm.

</details>

## Note

All changes will be submitted via pull requests when Stage 1 and README are completed, to practice a standard collaborative workflow.
