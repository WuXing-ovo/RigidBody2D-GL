#include "physics/ball.hpp"
#include "physics/world.hpp"
#include "raylib.h"
#include <iostream>
#include <span>

int main()
{
    World world;
    world.set_size(1920, 1080);
    world.set_gravity(0, -9.8);

    // Add two balls with random properties
    world.add_random_Balls(100, vec2{-100, -100}, vec2{100, 100}, 1, 5, 5, 10);

    // Visualization
    // Set screen size
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    // Initialize the screen
    InitWindow(screenWidth, screenHeight, "RigidBody2D");

    // Set fps
    int Fps = 60;
    SetTargetFPS(Fps);

    // Main loop
    while (!WindowShouldClose())
    {
        world.simulate(1);
        world.print_state();
        // Get Balls
        std::span<const Ball> all_balls = world.get_Balls(0, 100);

        BeginDrawing();
        ClearBackground(WHITE);
        // Add balls to the screen
        for (const auto &ball : all_balls)
        {
            auto position = ball.get_position();
            auto radius = ball.get_size();

            DrawCircle(position.x, position.y, radius, BLUE);
        }

        // Draw frame informations
        DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Frame time: %02.02f ms", GetFrameTime()), 10, 30, 20, DARKGRAY);

        EndDrawing();
    }
    CloseWindow();
}
