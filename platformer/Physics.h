#pragma once
#include "Common.h"
#include "Entity.h"

#include <memory>
namespace Physics
{
    // return overlap rectangle size
    // if not found return Vec2<0, 0>
    Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
}
