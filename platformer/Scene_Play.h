#pragma once

#include "Common.h"
#include "Components.h"
#include "GameEngine.h"
#include "Action.h"
#include "Scene.h"
#include "EntityManager.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <fstream>
#include <functional>

class Scene_Play : public Scene
{

    struct PlayerConfig
    {
        int X, Y;
        float CX, CY, S, MAX_S, JUMP, GRAVITY;

        void set(std::ifstream & fin);
    };

protected:

    std::shared_ptr<Entity> m_player;
    std::shared_ptr<sf::VertexArray> m_grid;
    std::string m_levelPath;
    PlayerConfig m_playerConfig;
    bool m_drawTextures = true;
    bool m_drawCollision = false;
    bool m_drawGrid = false;
    const Vec2 m_gridSize = { 16, 16 };
    sf::Text m_gridText;

    void init(const std::string & levelPath);
    void createGrid();
    void loadLevel(const std::string &);
    Vec2 gridToMidPixel(int, int, std::shared_ptr<Entity>);
    void spawnPlayer(const std::string &, const std::string & = "idle");


    void sMovement();
    void sLifespan();
    void sCollision();
    void sAnimation();
    void sRender();
    void sDrawGrid();

    void update();

public:

    Scene_Play(GameEngine * gameEngine, const std::string & levelPath);
    void sDoAction(const Action & action);
};

