#pragma once

#include "Common.h"
#include "Components.h"
#include "GameEngine.h"
#include "Action.h"
#include "Scene.h"
#include "EntityManager.h"

class Scene_Play : public Scene
{

    struct PlayerConfig
    {
        int X, Y;
        float CX, CY, S, MAX_S, JUMP, GRAVITY;
    };

protected:

    std::shared_ptr<Entity> m_player;
    std::string m_levelPath;
    PlayerConfig m_playerConfig;
    bool m_drawTextures = true;
    bool m_drawCollision = false;
    bool m_drawGrid = false;
    const Vec2 m_gridSize = { 16, 16 };
    sf::Text m_gridText;

    void init(const std::string & levelPath);
    void loadLevel(const std::string &);
    Vec2 gridToMidPixel(int, int, std::shared_ptr<Entity>);
    void sDoAction(const Action & action);
    void sMovement();


public:

    Scene_Play(GameEngine * gameEngine, const std::string & levelPath);
};

