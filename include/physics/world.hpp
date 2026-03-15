#pragma once
#include "physics/ball.hpp"
#include <vector>

class World
{
private:
    // Size of the panel
    double width;
    double height;
    // Gravaty
    double gravity_y;
    // Balls
    std::vector<Ball> balls;
    // Step length
    double dt;

public:
    // Constructor
    World() : width(1), height(1), gravity_y(0), dt(0.01) {}
    // Setters
    void set_size(double x = 1, double y = 1);
    void set_gravity(double g = 0);
    void add_Ball(Ball &&b);
    void add_Balls(std::vector<Ball> &&bs);
    void set_dt(double s = 0.01);
};