#include "GameEngine.h"
#include <SFML/Window/Keyboard.hpp>
#include <string>

void GameEngine::init(const std::string & path)
{

    m_window.create(sf::VideoMode(1280, 768), "Vikking");
    // 60 fps
    m_window.setFramerateLimit(60);
    // load assets
    m_assets.loadFromFile(m_source_dir, path);

    // presave keyboards
    m_inputToActionMap[sf::Keyboard::W] = Action(sf::Keyboard::W);
    m_inputToActionMap[sf::Keyboard::A] = Action(sf::Keyboard::A);
    m_inputToActionMap[sf::Keyboard::S] = Action(sf::Keyboard::S);
    m_inputToActionMap[sf::Keyboard::D] = Action(sf::Keyboard::S);
    m_inputToActionMap[sf::Keyboard::Space] = Action(sf::Keyboard::Space);
    m_inputToActionMap[sf::Keyboard::C] = Action(sf::Keyboard::C);
    m_inputToActionMap[sf::Keyboard::T] = Action(sf::Keyboard::T);
    m_inputToActionMap[sf::Keyboard::G] = Action(sf::Keyboard::G);
    m_inputToActionMap[sf::Keyboard::P] = Action(sf::Keyboard::P);
    m_inputToActionMap[sf::Keyboard::Escape] = Action(sf::Keyboard::Escape);
}


std::shared_ptr<Scene> GameEngine::currentScene()
{
    return m_sceneMap[m_currentScene];
}

void GameEngine::changeScene(
        const std::string & sceneName,
        std::shared_ptr<Scene> scene,
        bool endCurrentScene
        )
{
    if (endCurrentScene)
        m_sceneMap[sceneName] = scene;
    m_currentScene = sceneName;
}

void GameEngine::sUserInput()
{
    sf::Event event;

    auto scene = currentScene();

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;

        if (event.type == sf::Event::KeyPressed)
        {
            if (m_inputToActionMap.find(event.key.code) != m_inputToActionMap.end())
            {
                Action & action = m_inputToActionMap[event.key.code];
                action.setType("START");
                scene->sDoAction(action);
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (m_inputToActionMap.find(event.key.code) != m_inputToActionMap.end())
            {
                Action & action = m_inputToActionMap[event.key.code];
                action.setType("END");
                scene->sDoAction(action);
            }
        }
    }
}

void GameEngine::update()
{

}

void GameEngine::run()
{
    while (m_running)
    {
    }
}

