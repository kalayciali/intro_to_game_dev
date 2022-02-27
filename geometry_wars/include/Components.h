#pragma once

#include "Common.h"
#include <SFML/System/Vector2.hpp>

struct CTransform
{
    Vec2 pos;
    Vec2 velocity;
    float angle;

    CTransform() : angle(1.f) {}
    CTransform(const Vec2 & p, const Vec2 & v, float a)
        : pos(p), velocity(v), angle(a) { }
};

struct CShape
{
    // every shape in game is circle
    sf::CircleShape circle;

    CShape(float radius, int points, 
            const sf::Color & fill, const sf::Color & outline,
            float thickness)
        : circle(radius, points)
    {
        // every entity is circle
        circle.setFillColor(fill);
        circle.setOutlineThickness(thickness);
        circle.setOutlineColor(outline);
        // set origin to center point
        sf::Vector2f origin = { radius, radius };
        circle.setOrigin(origin);
    }
};


struct CCollision
{
    float radius;

    CCollision() : radius(0.f) {}
    CCollision(float r)
        : radius(r) {}
};

struct CScore
{
    int score;

    CScore() : score(0) {}
    CScore(int s)
        : score(s) {}
};

struct CLifespan
{
    int lifespan = 0;
    int created_at = 0;

    CLifespan(int duration, int start_frame)
        : lifespan(duration), created_at(start_frame) {}

    int currentFrame() { return lifespan + created_at; }
};

struct CInput
{
    bool left;
    bool right;
    bool down;
    bool up;
    bool shoot;
    bool spec;

    CInput() 
        : left(false), right(false), down(false), 
        up(false), shoot(false), spec(false){}
};
