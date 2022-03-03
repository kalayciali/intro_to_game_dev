#include "Scene.h"

Scene::Scene(GameEngine * game)
    : m_game(game),
    m_currentFrame(0),
    m_paused(false), m_hasEnded(false)
{  }

void Scene::registerAction(int key, bool * input)
{
    m_actionMap[key] = input;
}

