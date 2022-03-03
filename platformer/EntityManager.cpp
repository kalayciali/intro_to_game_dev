#include <algorithm>

#include "EntityManager.h"


bool ifAlive(ptr<Entity> e)
{
    return e->isAlive();
}


ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
    // couldn't use make_shared
    // private Entity ctor
    auto e = ptr<Entity>(new Entity(tag, m_totalEntities++));
    m_toAdd.push_back(e);
    return e;
}

void EntityManager::removeDead(EntityVec & entities)
{
    EntityVec::iterator dead = std::partition(
            entities.begin(), entities.end(), ifAlive);
    entities.erase(dead, entities.end());
}

void EntityManager::update()
{
    // called at the beginning of each frame by game engine
    // delayed action in order to avoid iterator invalidation
    removeDead(m_entities);

    for (auto & [tag, entityVec] : m_entityMap)
    {
        removeDead(entityVec);
    }

    for (auto e : m_toAdd)
    {
        m_entities.push_back(e);
        m_entityMap[e->tag()].push_back(e);
    }

    m_toAdd.clear();
}



EntityVec & EntityManager::getEntities()
{
    return m_entities;
}

EntityVec & EntityManager::getEntities(const std::string & tag)
{
    return m_entityMap[tag];
}

