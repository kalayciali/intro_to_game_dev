#include "Scene.h"
#include <string>

Scene::Scene(GameEngine * game)
    : m_game(game),
    m_currentFrame(0),
    m_paused(false), m_hasEnded(false)
{  }

void Scene::registerAction(int key, const std::string & command)
{
    m_actionMap[key] = command;
}

