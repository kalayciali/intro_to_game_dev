#pragma once

#include "Common.h"
#include "Components.h"

class Entity
{
    bool m_alive = true;
    const size_t m_id = 0;
    const std::string m_tag = "default";

    // friend factory forward declaration
    friend class EntityManager;
    // private ctor
    // only factory can construct entities
    Entity(const std::string & tag, size_t id)
        : m_id(id), m_tag(tag) {}

public:

    // make components shared ptr
    // new variable in entity for each component
    // if not set, it is nullptr
    std::shared_ptr<CTransform> c_transform;
    std::shared_ptr<CShape> c_shape;
    std::shared_ptr<CCollision> c_collision;
    std::shared_ptr<CScore> c_score;
    std::shared_ptr<CLifespan> c_lifespan;
    std::shared_ptr<CInput> c_input;

    const std::string & tag() const { return m_tag; }
    bool isAlive() const { return m_alive; }
    size_t id() const { return m_id; }
    void destroy() { m_alive = false; }
};

