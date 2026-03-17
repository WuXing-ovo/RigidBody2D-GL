#pragma once
#include <stdexcept>
#include "vec2.hpp"

class Ball
{
    private:
    vec2 position;
    vec2 velocity;
    double mass;
    double size;

    public:
    // Constructors
    Ball(): position {0.0, 0.0}, velocity {0.0, 0.0}, mass(0.0), size(0.0) {}

    // Public methods
    // Set parameters
    void set_position(double x=0, double y=0);
    void set_position(const vec2 &position_in);
    void set_velocity(double x_dot=0, double y_dot=0);
    void set_velocity(const vec2 &velocity_in);
    void set_mass(double m=0);
    void set_size(double size=0);
    // Get parameters
    const vec2& get_position() const;
    const vec2& get_velocity() const;
    double get_mass() const;
    double get_size() const;
};