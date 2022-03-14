#include "GameEngine.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
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
    m_inputToActionMap[sf::Keyboard::D] = Action(sf::Keyboard::D);
    m_inputToActionMap[sf::Keyboard::Space] = Action(sf::Keyboard::Space);
    m_inputToActionMap[sf::Keyboard::C] = Action(sf::Keyboard::C);
    m_inputToActionMap[sf::Keyboard::T] = Action(sf::Keyboard::T);
    m_inputToActionMap[sf::Keyboard::G] = Action(sf::Keyboard::G);
    m_inputToActionMap[sf::Keyboard::P] = Action(sf::Keyboard::P);
    m_inputToActionMap[sf::Keyboard::Escape] = Action(sf::Keyboard::Escape);

    // dont presave mouse actions
    // they are basic enum
    // will cause key collision
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

        // in current setup don't give permission
        // to use keyboard and mouse at the same time
        // because they are simple enums

        if (event.type == sf::Event::KeyPressed)
        {
            if (m_inputToActionMap.find(event.key.code) != m_inputToActionMap.end())
            {
                Action & action = m_inputToActionMap[event.key.code];
                action.setType("START");
                currentScene()->sDoAction(action);
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (m_inputToActionMap.find(event.key.code) != m_inputToActionMap.end())
            {
                Action & action = m_inputToActionMap[event.key.code];
                action.setType("END");
                currentScene()->sDoAction(action);
            }
        }

        // mouse events
        auto mousePos = sf::Mouse::getPosition(m_window);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left:
                    {
                        Action mouse(sf::Mouse::Left, "MOUSE", "START");
                        mouse.setPos(mousePos.x, mousePos.y);
                        currentScene()->sDoAction(mouse);
                        break;
                    }

                case sf::Mouse::Right:
                    {
                        Action mouse(sf::Mouse::Right, "MOUSE", "START");
                        mouse.setPos(mousePos.x, mousePos.y);
                        currentScene()->sDoAction(mouse);
                        break;
                    }
                default: break;
            }
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Left:
                    {
                        Action mouse(sf::Mouse::Left, "MOUSE", "START");
                        mouse.setPos(mousePos.x, mousePos.y);
                        currentScene()->sDoAction(mouse);
                        break;
                    }

                case sf::Mouse::Right:
                    {
                        Action mouse(sf::Mouse::Right, "MOUSE", "START");
                        mouse.setPos(mousePos.x, mousePos.y);
                        currentScene()->sDoAction(mouse);
                        break;
                    }
                default: break;
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            // here 6 is set to mousemove
            Action mouse(6, "MOUSE", "MOUSE_MOVE");
            mouse.setPos(event.mouseMove.x, event.mouseMove.y);
            currentScene()->sDoAction(mouse);
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

