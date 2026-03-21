#pragma once
#include "physics/ball.hpp"
#include "physics/vec2.hpp"
#include <vector>
#include <span>

// Template for x square
template <typename T>
T sqr(T x)
{
    return x * x;
}

class World
{
private:
    // Size of the panel
    vec2 world_size;
    // Gravaty
    vec2 gravity;
    // Balls
    std::vector<Ball> balls;
    // Step length
    double dt;
    // Coefficient of restitution
    double restitution;
    // Frame count
    size_t frame;
    // Private Methods
    void update_velocity(Ball &ball_1, Ball &ball_2);
    

public:
    // Constructor
    World() : dt(0.01), restitution(1), frame(0) {}
    // Setters
    void set_size(double x = 1, double y = 1);
    void set_size(const vec2 &world_size_in);
    void set_gravity(double gx = 0, double gy = 0);
    void set_gravity(const vec2 &g);
    void add_Ball(Ball &&b);
    void add_Balls(std::vector<Ball> &&bs);
    void set_dt(double s = 0.01);
    // Getters
    const vec2 &get_size() const;
    const vec2 &get_gravity() const;
    Ball &get_Ball(size_t index);
    const Ball &get_Ball(size_t index) const;
    std::span<Ball> get_Balls(size_t start, size_t end);
    std::span<const Ball> get_Balls(size_t start, size_t end) const;
    // Trace compute step by step
    void step();
    // Collision detect
    void collision_detect();
    void print_state() const;
    void simulate(size_t steps);
};