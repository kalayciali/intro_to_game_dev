#pragma once

#include "Entity.h"
#include "Common.h"
#include <memory>

// EntityVec is all entities
typedef std::vector<std::shared_ptr<Entity>> EntityVec;
// EntityMap is entities grouped by their tag
typedef std::map<std::string, EntityVec> EntityMap;

class EntityManager
{
    EntityVec m_entities;
    EntityMap m_entityMap;
    size_t m_totalEntities;

    // to avoid iterator invalidation
    EntityVec m_toAdd;
    void removeDead(EntityVec &);

public:

    EntityManager() : m_totalEntities(0) {}

    void update();
    std::shared_ptr<Entity> addEntity(const std::string & tag);
    EntityVec & getEntities();
    EntityVec & getEntities(const std::string & tag);
};

// helper predicate func
bool ifAlive(std::shared_ptr<Entity>);
