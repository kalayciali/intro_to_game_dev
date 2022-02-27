#include "Vec2.h"
#include <stdexcept>
#include <cmath>

float Vec2::dist(const Vec2 & rhs) const
{
    float x_diff = rhs.x - x;
    float y_diff = rhs.y - y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

float Vec2::magnitude() const
{
    return sqrt(x * x + y * y);
}

// member operators 
//
bool Vec2::operator==(const Vec2 & rhs) const
{ 
    return x == rhs.x && y == rhs.y; 
}

bool Vec2::operator!=(const Vec2 & rhs) const
{ 
    return x != rhs.x || y != rhs.y; 
} 


void Vec2::operator+=(const Vec2 & rhs)
{
    x += rhs.x;
    y += rhs.y;
}

void Vec2::operator-=(const Vec2 & rhs)
{
    x -= rhs.x;
    y -= rhs.y;
}

void Vec2::operator*=(float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator/=(float val)
{
    if (val == 0.f)
        throw(std::logic_error("division by zero"));
    x /= val;
    y /= val;
}


// nonmember operators
// num will be implicitly converted to Vec2(num, num)

Vec2 operator+(const Vec2 & lhs, const Vec2 & rhs) 
{ 
    return Vec2(lhs.x + rhs.x, lhs.y + rhs.y); 
}

Vec2 operator-(const Vec2 & lhs, const Vec2 & rhs)
{
    return Vec2(lhs.x - rhs.x, lhs.y - rhs.y );
}

Vec2 operator*(const Vec2 & lhs, const Vec2 & rhs)
{
    return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
}

Vec2 operator/(const Vec2 & lhs, const Vec2 & rhs)
{
    if (rhs.y == 0.f || rhs.x == 0.f)
        throw(std::logic_error("division by zero"));
    return Vec2(lhs.x / rhs.x, lhs.y / rhs.y);
}


std::ostream & operator<<(std::ostream & stream, const Vec2 & vec)
{
    return stream << vec.x << " " << vec.y << "\n";
}

