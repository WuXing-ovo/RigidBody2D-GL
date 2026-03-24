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
    size_t ID;

public:
    // Constructors
    Ball() : position{0.0, 0.0}, velocity{0.0, 0.0}, mass(0.0), size(0.0), ID(0) {}

    // Public methods
    // Set parameters

    /// @brief Set initial positions
    /// @param x Initial x position
    /// @param y Initial y position
    void set_position(double x = 0, double y = 0);

    /// @brief Set initial positions with a vec2 input
    /// @param position_in A vec2 contains original position of the ball
    void set_position(const vec2 &position_in);

    /// @brief Set initial velocity
    /// @param x_dot Initial x velocity
    /// @param y_dot Initial y velocity
    void set_velocity(double x_dot = 0, double y_dot = 0);

    /// @brief Set initial velocity with vec2 input
    /// @param velocity_in A vec2 contains original velocity of the ball
    void set_velocity(const vec2 &velocity_in);

    /// @brief Set mass for the ball
    /// @param m Mass
    void set_mass(double m = 0);

    /// @brief Set radius for the ball
    /// @param size Radius
    void set_size(double size = 0);

    /// @brief Set ID for the ball
    /// @param ID_in ID
    void set_ID(size_t ID_in);
    // Get parameters

    /// @brief Get position of the ball
    /// @return A const vec2 contains position
    const vec2 &get_position() const;

    /// @brief Get velocity of the ball
    /// @return A const vec2 contains velocity
    const vec2 &get_velocity() const;

    /// @brief Get mass of the ball
    /// @return Mass
    double get_mass() const;

    /// @brief Get radius of the ball
    /// @return Radius
    double get_size() const;

    /// @brief Get ID of the ball
    /// @return ID
    size_t get_ID() const;
};