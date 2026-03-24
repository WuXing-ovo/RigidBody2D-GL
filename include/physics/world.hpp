#pragma once
#include "physics/ball.hpp"
#include "physics/vec2.hpp"
#include <vector>
#include <span>
#include <random>

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
    // Ball count for ID tracking
    size_t ball_count;
    // Random seed
    std::mt19937 rng;
    // Private Methods
    void update_velocity(Ball &ball_1, Ball &ball_2);

    /// @brief Sort balls by ID
    void sort_by_ID();

    /// @brief Calculate the movement of each ball during every dt and update their position
    void step();

    /// @brief Detect collision and update their velocity
    void collision_detect();

public:
    // Constructor
    World() : dt(0.01), restitution(1), frame(0), ball_count(0), rng(std::random_device{}()) {}
    // Setters

    /// @brief Set the world boundaries
    /// @param x Maximum of x axis
    /// @param y Maximum of y axis
    void set_size(double x = 1, double y = 1);

    /// @brief Overload set_size() for const vec2 input
    /// @param world_size_in A vec2 contains the world boundaries
    void set_size(const vec2 &world_size_in);

    /// @brief Set the world gravities
    /// @param gx A constant acceleration on x axis
    /// @param gy A constant acceleration on y axis
    void set_gravity(double gx = 0, double gy = 0);

    /// @brief Overload set_gravity() for vec2 input
    /// @param g A vec2 contains acceleration on two axises
    void set_gravity(const vec2 &g);

    /// @brief Add a single ball to the world with automatic ID assignment
    /// @param b Ball to add (ownership transfered via move)
    void add_Ball(Ball &&b);

    /// @brief Add multiple balls with automatic sequential ID assignment
    /// @param new_balls Vector of balls to add (ownership transfered)
    void add_Balls(std::vector<Ball> &&new_balls);

    /// @brief Add a random ball to the world
    /// @param v_min Minimum velocity range
    /// @param v_max Maximum velocity range
    /// @param mass_min Minimum mass
    /// @param mass_max Maximum mass
    /// @param size_min Minimum size
    /// @param size_max Maximum size
    void add_random_Ball(const vec2 &v_min, const vec2 &v_max, double mass_min, double mass_max, double size_min, double size_max);

    /// @brief Add random balls to the world
    /// @param num Number of random balls
    /// @param v_min Minimum of velocity
    /// @param v_max Maximum of velocity
    /// @param mass_min Minimum of mass
    /// @param mass_max Maximum of mass
    /// @param size_min Minimum of size
    /// @param size_max Maximum of size
    void add_random_Balls(size_t num, const vec2 &v_min, const vec2 &v_max, double mass_min, double mass_max, double size_min, double size_max);

    /// @brief Set dt
    /// @param s dt
    void set_dt(double s = 0.01);
    // Getters

    /// @brief Get the world size
    /// @return A vec2 contains world size
    const vec2 &get_size() const;

    /// @brief Get the world gravity
    /// @return A vec2 contains world gravity
    const vec2 &get_gravity() const;

    /// @brief Get a single ball from the world
    /// @param index Index of the needed ball
    /// @return A Ball class
    Ball &get_Ball(size_t index);

    /// @brief Overload of get_ball(), designed for constant condition
    /// @param index Index of the needed ball
    /// @return A constant Ball class
    const Ball &get_Ball(size_t index) const;

    /// @brief Get a bunch of balls
    /// @param start Start index in the ball vector
    /// @param end End index in the ball vector
    /// @return A vector contains balls you need
    std::span<Ball> get_Balls(size_t start, size_t end);

    /// @brief Overload of get_Balls(), designed for constant condition
    /// @param start Start index in the ball vector
    /// @param end End index in the ball vector
    /// @return A const vector contains balls you need
    std::span<const Ball> get_Balls(size_t start, size_t end) const;

    /// @brief Print world state with all balls
    void print_state();

    /// @brief Print part of all balls
    /// @param start Start index
    /// @param end End index
    void print_state(size_t start, size_t end);

    /// @brief Start simulation steps times
    /// @param steps Steps you want to forward
    void simulate(size_t steps);
};