#pragma once

struct vec2
{
    double x;
    double y;

    // Constructors
    vec2() : x(0), y(0) {}
    vec2(double x_in, double y_in) : x(x_in), y(y_in) {}
    // Operator overloads
    vec2 operator+(const vec2 &vec2_in) const
    {
        return vec2(x + vec2_in.x, y + vec2_in.y);
    }
    vec2 operator-(const vec2 &vec2_in) const
    {
        return vec2(x - vec2_in.x, y - vec2_in.y);
    }
    vec2 operator*(double scalar) const
    {
        return vec2(x * scalar, y * scalar);
    }
    friend vec2 operator*(double scalar, const vec2 &vec2_in)
    {
        return vec2_in * scalar;
    }
    vec2 &operator+=(const vec2 &vec2_in)
    {
        x += vec2_in.x;
        y += vec2_in.y;
        return *this;
    }
    vec2 &operator-=(const vec2 &vec2_in)
    {
        x -= vec2_in.x;
        y -= vec2_in.y;
        return *this;
    }
    double dot(const vec2 &other) const
    {
        return x * other.x + y * other.y;
    }
};