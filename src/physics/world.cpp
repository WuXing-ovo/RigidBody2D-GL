#include "physics/world.hpp"
#include <stdexcept>
#include <iterator>
#include <utility>
#include <span>

void World::set_size(double x, double y)
{
    if (x <= 0 || y <= 0)
    {
        throw std::invalid_argument("x and y must be positive!\n");
    }
    width = x;
    height = y;
}

void World::set_gravity(double g)
{
    gravity_y = g;
}

void World::add_Ball(Ball &&b)
{
    balls.emplace_back(std::move(b));
}

void World::add_Balls(std::vector<Ball> &&new_balls)
{
    balls.reserve(balls.size() + new_balls.size());
    balls.insert(balls.end(), std::make_move_iterator(new_balls.begin()), std::make_move_iterator(new_balls.end()));
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
double World::get_width() const
{
    return width;
}

double World::get_height() const
{
    return height;
}

double World::get_gravity() const
{
    return gravity_y;
}

Ball &World::get_Ball(size_t index)
{
    if (index < 0)
    {
        throw std::invalid_argument("Index can't be negative!\n");
    }
    else if (index >= balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return balls[index];
}

const Ball &World::get_Ball(size_t index) const
{
    if (index < 0)
    {
        throw std::invalid_argument("Index can't be negative!\n");
    }
    else if (index >= balls.size())
    {
        throw std::invalid_argument("Index is out of range!\n");
    }
    return balls[index];
}

std::span<Ball> World::get_Balls(size_t start, size_t end)
{
    if (start < 0 || end < 0)
    {
        throw std::invalid_argument("Start or end can't be negative!\n");
    }
    else if (start > end)
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
    if (start < 0 || end < 0)
    {
        throw std::invalid_argument("Start or end can't be negative!\n");
    }
    else if (end < start)
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
        each_ball.set_velocity(each_ball.get_velocity().x, each_ball.get_velocity().y - gravity_y * dt);
        each_ball.set_position(each_ball.get_position().x + each_ball.get_velocity().x * dt,
                               each_ball.get_position().y + each_ball.get_velocity().y * dt);
    }
}