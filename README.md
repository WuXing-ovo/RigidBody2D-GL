# RigidBody2D-GL

## Overview

A 2D rigid body physics simulation engine with OpenGL visualization, written in C++.

Now, it's still under development.

## Current Status

Stage 1: Core physics engine - Complete
Currently: Polishing and planning Stage 2

## Features

- CMake-based build setup
- A reasonable file structure
- Designed for future performance optimization
- High-performance collision detecting algorithm.

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

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
./RigidBody2D-GL
```

## Quick Start

```cpp
World world;
world.set_size(800, 600);
world.set_gravity(0, -9.8);

Ball ball;
ball.set_position(100, 100);
ball.set_velocity(5, 0);
ball.set_size(5);
world.add_Ball(std::move(ball));

// Run 100 simulation steps
world.simulate(100);
world.print_state();
```

## Physical Model

- **Coefficient of restitution**: $$C_r = \left| \frac{\mathbf{u}_f \cdot \hat{\mathbf{n}}}{\mathbf{u}_i \cdot \hat{\mathbf{n}}} \right|$$
  where $\mathbf{u}_i$ is initial velocity, $\mathbf{u}_f$ is final velocity.
- **Velocity**: $v_{a} = \frac{m_{a}u_{a}+m_{b}u_{b}+m_{b}C_{r}(u_{b}-u_{a})}{m_{a}+m_{b}}$ and $v_{b} = \frac{m_{a}u_{a}+m_{b}u_{b}+m_{a}C_{r}(u_{a}-u_{b})}{m_{a}+m_{b}}$

## Roadmap

The whole project is divided into three stages.

- **Stage 1**: A 2D RigidBody Simulation Engine in C++
- **Stage 2**: Improve performance with OpenMP and cache optimization
- **Stage 3**: Visualization with OpenGL

## Note

All changes will be submitted via pull requests when Stage 1 and README are completed, to practice a standard collaborative workflow.
