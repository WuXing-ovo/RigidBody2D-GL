#include "physics/ball.hpp"

void Ball::set_position(double x, double y){
    // Use this pattern instead of `position.x = x` for better readability
    position = {x, y};
}

void Ball::set_position(const vec2 &position_in){
    position = position_in;
}

void Ball::set_velocity(double x_dot, double y_dot){
    velocity = {x_dot, y_dot};
}

void Ball::set_velocity(const vec2 &velocity_in){
    velocity = velocity_in;
}

void Ball::set_mass(double m){
    if(m < 0){
        throw std::invalid_argument("Mass can't be negative!\n");
    }
    mass = m;
}

void Ball::set_size(double r){
    if(r < 0){
        throw std::invalid_argument("Radius can't be negative!\n");
    }
    size = r;
}

const vec2& Ball::get_position() const{
    return position;
}

const vec2& Ball::get_velocity() const{
    return velocity;
}

double Ball::get_mass() const{
    return mass;
}

double Ball::get_size() const {
    return size;
}