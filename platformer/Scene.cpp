#include "Scene.h"
#include <string>


void Scene::registerCommand(int key, std::function<void(Action)> command, const std::string & name)
{
    if (name == "KEY")
        m_keyToCommand[key] = command;
    else if (name == "MOUSE")
        m_mouseToCommand[key] = command;
}

