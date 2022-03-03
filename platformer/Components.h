#pragma once

#include "Animation.h"
#include "Assets.h"
#include <string>

struct Component
{
    bool has = false;
};

struct CTransform : public Component
{
    Vec2 pos = { 0.0, 0.0 };
    // for checking previous overlap
    Vec2 prevPos = { 0.0, 0.0 };
    Vec2 scale = { 1.0, 1.0 };
    Vec2 velocity = { 0.0, 0.0 };
    float angle = 0;

    CTransform() {}
    CTransform(const Vec2 & p) : pos(p), prevPos(p) {}
    CTransform(const Vec2 & p, const Vec2 & vel, const Vec2 & sc, float a) 
        : pos(p), prevPos(p), scale(sc), velocity(vel), angle(a) {}
};

struct CLifespan : public Component
{
    int finishAt = 0;
    int createdAt= 0;

    CLifespan(int duration, int startFrame)
        : createdAt(startFrame), finishAt(startFrame + duration) {}

};


struct CInput
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool attack = false;
    bool canAttack = false;
    bool canJump = false;

    bool toggleCollision = false;
    bool toggleGrid = false;
    bool toggleTexture = false;
    bool quit = false;
    bool pause = false;

    CInput();
};

struct CBBox: public Component
{
    // keep track of halfsize
    // origin is center of shape
    Vec2 size;
    Vec2 halfSize;

    CBBox(const Vec2 & s)
        : size(s), halfSize(s.x / 2, s.y / 2) {}
};

struct CAnimation : public Component
{
    Animation animation;
    bool repeat;
    CAnimation(const Animation & anim, bool r = true)
        : animation(anim), repeat(r){ }
};

struct CGravity : public Component
{
    float gravity = 0.f;
    CGravity(float g) : gravity(g) {}
};

struct CState : public Component
{
    std::string state = "jumping";
    CState(const std::string & s) : state(s) {}
};


