#pragma once

#include "Common.h"
#include "Assets.h"
#include "Scene.h"
#include "Action.h"
#include <SFML/Graphics/RenderWindow.hpp>

typedef std::map<std::string, std::shared_ptr<Scene> > SceneMap;

class GameEngine
{

    std::map<int, Action> m_inputToActionMap;
    void init(const std::string & path);

protected:
    // accessible via pointer
    std::string m_source_dir = "dir";
    sf::RenderWindow m_window;
    Assets m_assets;
    std::string m_currentScene;
    SceneMap m_sceneMap;
    bool m_running = true;

    void update();
    void quit() { m_running = false; }


    std::shared_ptr<Scene> currentScene();
    void changeScene(
            const std::string & sceneName,
            std::shared_ptr<Scene> scene,
            bool endCurrentScene = false
            );

    void sUserInput();

public:

    GameEngine(const std::string & path) { init(path); }


    void run();

    sf::RenderWindow & window() const { return m_window; }
    const Assets & assets() const { return m_assets; }
};
