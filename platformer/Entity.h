#pragma once

#include "Common.h"
#include "Components.h"
#include <tuple>

typedef std::tuple< 
    CTransform,
    CLifespan,
    CInput,
    CBBox,
    CAnimation,
    CGravity,
    CState > ComponentTuple;



class Entity
{
    // friend factory forward declaration
    friend class EntityManager;

    bool m_alive = true;
    size_t m_id = 0;
    std::string m_tag = "default";

    ComponentTuple m_components;

    // private ctor
    // only factory can construct entities
    Entity(const std::string & tag, size_t id)
        : m_id(id), m_tag(tag) {}

public:

    const std::string & tag() const { return m_tag; }
    size_t id() const { return m_id; }
    void destroy() { m_alive = false; }
    bool isAlive() const { return m_alive; }

    template <typename T>
        bool hasComponent() const
        {
            return getComponent<T>().has;
        }

    template <class T, class... tArgs>
        T & addComponent(tArgs&&... mArgs)
        {
            auto & component = getComponent<T>();
            component = T(std::forward<tArgs>(mArgs)...);
            component.has = true;
            return component;
        }

    template <class T>
        T & getComponent()
        {
            return std::get<T>(m_components);
        }

    template <class T>
        const T & getComponent() const
        {
            return std::get<T>(m_components);
        }
};

