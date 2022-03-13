#pragma once

#include <iostream>

class Vec2
{

public:

    float x;
    float y;

    Vec2() : x(0.f), y(0.f) {}
    // implicit conversion
    Vec2(float val): x(val), y(val) {}
    Vec2(float xin, float yin)
        : x(xin), y(yin) {}

    float magnitude() const;
    Vec2 abs() const;

    void print() 
    { std::cout << "<" << x << ", " << y << ">" << std::endl; } 

    // member operators
    bool operator==(const Vec2 & rhs) const;
    bool operator!=(const Vec2 & rhs) const;

    void operator+=(const Vec2 & rhs);
    void operator-=(const Vec2 & rhs);
    void operator*=(float val);
    void operator/=(float val);
    operator bool();

    float dist(const Vec2 & rhs) const;

};

Vec2 operator+(const Vec2 & lhs, const Vec2 & rhs);
Vec2 operator-(const Vec2 & lhs, const Vec2 & rhs);
Vec2 operator*(const Vec2 & lhs, const Vec2 & rhs);
Vec2 operator/(const Vec2 & lhs, const Vec2 & rhs);

std::ostream & operator<<(std::ostream & stream, const Vec2 & vec);
