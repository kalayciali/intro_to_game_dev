#include "EntityManager.h"
#include <algorithm>

bool ifAlive(ptr<Entity> e)
{
    return e->isAlive();
}


ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // couldn't use make_shared
    // private Entity ctor
    auto e = ptr<Entity>(new Entity(tag, m_total_entities++));
    m_to_add.push_back(e);
    return e;
}

void EntityManager::update()
{
    // called at the beginning of each frame by game engine
    // delayed action in order to avoid iterator invalidation
    removeDead(m_entities);

    for (auto & [tag, entity_vec] : m_entity_map)
    {
        removeDead(entity_vec);
    }

    for (auto e : m_to_add)
    {
        m_entities.push_back(e);
        m_entity_map[e->tag()].push_back(e);
    }

    m_to_add.clear();
}


void EntityManager::removeDead(EntityVec & entities)
{
    EntityVec::iterator dead = std::partition(
            entities.begin(), entities.end(), ifAlive);
    entities.erase(dead, entities.end());
}

EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entity_map[tag];
}

