#include "physics/world.hpp"
#include "physics/vec2.hpp"
#include <stdexcept>
#include <iterator>
#include <utility>
#include <span>
#include <cmath>
#include <iostream>
#include <random>

void World::set_size(double x, double y)
{
    if (x <= 0 || y <= 0)
    {
        throw std::invalid_argument("x and y must be positive!\n");
    }
    world_size = {x, y};
}

void World::set_size(const vec2 &world_size_in)
{
    if (world_size_in.x <= 0 || world_size_in.y <= 0)
    {
        throw std::invalid_argument("x and y must be positive!\n");
    }
    world_size = world_size_in;
}

void World::set_gravity(double gx, double gy)
{
    gravity = {gx, gy};
}

void World::set_gravity(const vec2 &g)
{
    gravity = g;
}

void World::add_Ball(Ball &&b)
{
    b.set_ID(ball_count);
    balls.emplace_back(std::move(b));
    ball_count++;
}

void World::add_Balls(std::vector<Ball> &&new_balls)
{
    for (auto &x : new_balls)
    {
        x.set_ID(ball_count);
        ball_count++;
    }
    balls.reserve(balls.size() + new_balls.size());
    balls.insert(balls.end(), std::make_move_iterator(new_balls.begin()), std::make_move_iterator(new_balls.end()));
}

void World::add_random_Ball(const vec2 &v_min, const vec2 &v_max, double mass_min, double mass_max, double size_min, double size_max)
{
    // Create a ball
    Ball ball_input;

    // Set size
    std::uniform_real_distribution<double> size(size_min, size_max);
    ball_input.set_size(size(rng));

    // Set position within the world_size
    std::uniform_real_distribution<double> position_x(ball_input.get_size(), world_size.x - ball_input.get_size());
    std::uniform_real_distribution<double> position_y(ball_input.get_size(), world_size.y - ball_input.get_size());
    ball_input.set_position(position_x(rng), position_y(rng));

    // Set velocity
    std::uniform_real_distribution<double> velocity_x(v_min.x, v_max.x);
    std::uniform_real_distribution<double> velocity_y(v_min.y, v_max.y);
    ball_input.set_velocity(vec2{velocity_x(rng), velocity_y(rng)});

    // Set mass
    std::uniform_real_distribution<double> mass(mass_min, mass_max);
    ball_input.set_mass(mass(rng));

    // Add the new ball to vector
    add_Ball(std::move(ball_input));
}

void World::add_random_Balls(size_t num, const vec2 &v_min, const vec2 &v_max, double mass_min, double mass_max, double size_min, double size_max)
{
    // Add balls with random properties by add_random_Ball()
    for (int i = 0; i < num; i++)
    {
        add_random_Ball(v_min, v_max, mass_min, mass_max, size_min, size_max);
    }
}

void World::set_dt(double s)
{
    if (s <= 0)
    {
        throw std::invalid_argument("dt must be positive!\n");
    }
    dt = s;
}

// Getters
const vec2 &World::get_size() const
{
    return world_size;
}

const vec2 &World::get_gravity() const
{
    return gravity;
}

Ball &World::get_Ball(size_t index)
{
    if (index >= balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return balls[index];
}

const Ball &World::get_Ball(size_t index) const
{
    if (index >= balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return balls[index];
}

std::span<Ball> World::get_Balls(size_t start, size_t end)
{
    if (start > end)
    {
        throw std::invalid_argument("End can't be smaller than start!\n");
    }
    else if (start > balls.size() || end > balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return std::span<Ball>(balls.begin() + start, balls.begin() + end);
}

std::span<const Ball> World::get_Balls(size_t start, size_t end) const
{
    if (end < start)
    {
        throw std::invalid_argument("End can't be smaller than start!\n");
    }
    else if (start > balls.size() || end > balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return std::span<const Ball>(balls.begin() + start, balls.begin() + end);
}

void World::step()
{
    for (auto &each_ball : balls)
    {
        each_ball.set_velocity(each_ball.get_velocity() + gravity * dt);
        each_ball.set_position(each_ball.get_position() + each_ball.get_velocity() * dt);
    }
}

void World::collision_detect()
{
    // Sort by x - r
    std::sort(balls.begin(), balls.end(), [](const Ball &a, const Ball &b)
              { return (a.get_position().x - a.get_size()) < (b.get_position().x - b.get_size()); });
    size_t index = 0;
    for (auto &each_ball : balls)
    {
        index++;
        for (auto &the_other : std::span(balls).subspan(index, balls.size() - index))
        {
            // x_1 + r_1 < x_2 - r_2
            // In a sorted ball list, there will be no more collided ball after first uncollided ball
            // So break after first uncollided ball
            if (each_ball.get_position().x + each_ball.get_size() < the_other.get_position().x - the_other.get_size())
            {
                break;
            }
            // Check y-axis gap if x-aixs is potentially colliding
            // Continue to skip next criteria when the gap of y is larger than the sum of radius
            if (std::fabs(each_ball.get_position().y - the_other.get_position().y) > each_ball.get_size() + the_other.get_size())
            {
                continue;
            }
            // Compute a precise distance
            // (x_1 - x_2) ** 2 + (y_1 - y_2) ** 2 = (r_1 + r_2) ** 2
            if (sqr(each_ball.get_position().x - the_other.get_position().x) + (sqr(each_ball.get_position().y - the_other.get_position().y)) <= sqr(each_ball.get_size() + the_other.get_size()))
            {
                update_velocity(each_ball, the_other);
            }
        }
        // Wall detection
        // Take the opposite velocity on the collided axis when the ball collide with the wall
        if (each_ball.get_position().x - each_ball.get_size() < 0)
        {
            each_ball.set_velocity(-each_ball.get_velocity().x, each_ball.get_velocity().y);
        }
        if (each_ball.get_position().x + each_ball.get_size() > world_size.x)
        {
            each_ball.set_velocity(-each_ball.get_velocity().x, each_ball.get_velocity().y);
        }
        if (each_ball.get_position().y - each_ball.get_size() < 0)
        {
            each_ball.set_velocity(each_ball.get_velocity().x, -each_ball.get_velocity().y);
        }
        if (each_ball.get_position().y + each_ball.get_size() > world_size.y)
        {
            each_ball.set_velocity(each_ball.get_velocity().x, -each_ball.get_velocity().y);
        }
    }
}

void World::update_velocity(Ball &ball_1, Ball &ball_2)
{
    // Note: This function won't check the validation of inputs, so don't use it without checking
    // Saclarization
    // Get normal vector between two balls
    const vec2 normal_vector = (ball_1.get_position() - ball_2.get_position()).normalized();

    // Velocity on normal direction
    const auto v1_i_normal = ball_1.get_velocity().dot(normal_vector);
    const auto v2_i_normal = ball_2.get_velocity().dot(normal_vector);

    // Get the velocity after collision
    // (m_1 * v1_i + m_2 * v2_i + C_r * m_2 * (v2_i - v1_i)) / (m_1 + m_2) and vice versa
    const auto v1_f_normal = (ball_1.get_mass() * v1_i_normal + ball_2.get_mass() * v2_i_normal + restitution * ball_2.get_mass() * (v2_i_normal - v1_i_normal)) / (ball_1.get_mass() + ball_2.get_mass());
    const auto v2_f_normal = (ball_1.get_mass() * v1_i_normal + ball_2.get_mass() * v2_i_normal + restitution * ball_1.get_mass() * (v1_i_normal - v2_i_normal)) / (ball_1.get_mass() + ball_2.get_mass());

    // Compute the difference between v1_f and v2_f
    const auto diff_of_1 = v1_f_normal - v1_i_normal;
    const auto diff_of_2 = v2_f_normal - v2_i_normal;

    // Vectorization
    const auto vec_diff_of_1 = diff_of_1 * normal_vector;
    const auto vec_diff_of_2 = diff_of_2 * normal_vector;

    // Update velocity
    ball_1.set_velocity(ball_1.get_velocity() - vec_diff_of_1);
    ball_2.set_velocity(ball_2.get_velocity() - vec_diff_of_2);
}

void World::print_state() const
{
    std::cout << "=== World State (Frame: " << frame << ") ===" << std::endl;
    for (auto ball : balls)
    {
        std::cout << "Ball " << ball.get_ID() << ": pos=" << ball.get_position() << " vel=" << ball.get_velocity() << " mass=" << ball.get_mass() << " r=" << ball.get_size() << std::endl;
    }
}

void World::simulate(size_t steps)
{
    for (size_t i = 0; i < steps; i++)
    {
        step();
        collision_detect();
        frame++;
    }
}