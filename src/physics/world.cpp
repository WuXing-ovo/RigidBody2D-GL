#include "physics/world.hpp"
#include <stdexcept>
#include <iterator>
#include <utility>

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