#include "Physics.h"
#include "Components.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{

    auto & aTransform = a->getComponent<CTransform>();
    auto & aBorder = a->getComponent<CBBox>();

    auto & bTransform = b->getComponent<CTransform>();
    auto & bBorder = b->getComponent<CBBox>();

    Vec2 diff = ( aTransform.pos - bTransform.pos ).abs();

    Vec2 overlap = aBorder.halfSize + bBorder.halfSize - diff;

    overlap.x = overlap.x > 0. ? overlap.x : 0.;
    overlap.y = overlap.y > 0. ? overlap.y : 0.;

    return overlap;
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    auto & aTransform = a->getComponent<CTransform>();
    auto & aBorder = a->getComponent<CBBox>();

    auto & bTransform = b->getComponent<CTransform>();
    auto & bBorder = b->getComponent<CBBox>();

    Vec2 diff = ( aTransform.prevPos - bTransform.prevPos ).abs();

    Vec2 overlap = aBorder.halfSize + bBorder.halfSize - diff;

    overlap.x = overlap.x > 0. ? overlap.x : 0.;
    overlap.y = overlap.y > 0. ? overlap.y : 0.;

    return overlap;
}
