#include "Scene_Play.h"
#include "Physics.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <fstream>
#include <memory>
#include "State.h"

void Scene_Play::PlayerConfig::set(std::ifstream & fin)
{
    fin >> X >> Y;
    fin >> CX >> CY;
    fin >> S >> JUMP;
    fin >> MAX_S >> GRAVITY;
}

void Scene_Play::createGrid()
{
    // 12 row and 20 cols for 64x64
    // multipy it with 4
    int rows = 4 * 12;
    int cols = 4 * 20;
    int numLines = rows + cols - 2;

    auto grid = std::make_shared<sf::VertexArray>(sf::Lines, 2 * numLines);

    auto size = m_game->m_window.getView().getSize();
    float rowH = size.y / rows;
    float colW = size.x / cols;
    // row seperators
    for (int i=0; i < rows; i++)
    {
        float rowY = rowH * i;
        (*grid)[i*2].position = { 0, rowY };
        (*grid)[i*2 + 1].position = { size.x, rowY };
    }
    // col seperators
    for (int i=0; i < cols; i++)
    {
        float colX = colW * i;
        (*grid)[rows + i*2].position = { colX, 0};
        (*grid)[rows + i*2 + 1].position = { size.y, colX };
    }

    m_grid = grid;
}

void Scene_Play::sDrawGrid()
{
    while (m_drawGrid)
    {
        m_game->m_window.draw(m_grid);
    }
}

Scene_Play::Scene_Play(GameEngine * gameEngine, const std::string & levelPath)
    : Scene(gameEngine),
    m_levelPath(levelPath)
{
    init(m_levelPath);
}

void Scene_Play::loadLevel(const std::string & fname)
{
    // reset the entity manager every time we load level
    m_entityFact = EntityManager();

    // use player config struct.
    // read level file, generate all entities appropriately
    std::ifstream fin(m_game->m_source_dir + fname);
    std::string inputType;

    createGrid();

    int gridX, gridY;
    std::string animName;
    while (fin >> inputType)
    {

        if (inputType == "Tile")
        {
            fin >> animName >> gridX >> gridY;

            auto tile = m_entityFact.addEntity("tile");
            tile->addComponent<CAnimation>(m_game->assets().getAnimation(animName));
            tile->addComponent<CTransform>(gridToMidPixel(gridX, gridY, tile));
            tile->addComponent<CBBox>(m_game->assets().getAnimation(animName).getSize());

        }

        else if (inputType == "Dec")
        {
            fin >> animName >> gridX >> gridY;

            auto dec = m_entityFact.addEntity("dec");
            dec->addComponent<CAnimation>(m_game->assets().getAnimation(animName));
            dec->addComponent<CTransform>(gridToMidPixel(gridX, gridY, dec));
        }

        else if (inputType == "P")
        {
            std::string stateName;

            fin >> animName;
            fin >> stateName;
            m_playerConfig.set(fin);
            spawnPlayer(animName, stateName);
        }
    }


    if (brick->getComponent<CAnimation>().animation.getName() == "brick")
    {

    }

    // components are now returned as references, so use references
    // auto & transform1 = entity->get<CTransform>()
}

void Scene_Play::spawnPlayer(const std::string & animName = "P_Idle", const std::string & stateName)
{
    auto player = m_entityFact.addEntity("player");

    player->addComponent<CAnimation>(m_game->assets().getAnimation(animName));
    player->addComponent<CInput>();
    player->addComponent<CTransform>(
            gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, player));
    player->addComponent<CBBox>({ m_playerConfig.CX, m_playerConfig.CY });
    player->addComponent<CGravity>( m_playerConfig.GRAVITY );
    player->addComponent<CState>(stateName);
    m_player = player;

}

void Scene_Play::init(const std::string & levelPath)
{
    loadLevel(levelPath);

    registerAction(sf::Keyboard::W, "JUMP");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::Space, "ATTACK");

    registerAction(sf::Keyboard::P, "PAUSE");
    registerAction(sf::Keyboard::Escape, "QUIT");
    registerAction(sf::Keyboard::T, "T_TEXTURE");
    registerAction(sf::Keyboard::C, "T_COLLISION");
    registerAction(sf::Keyboard::G, "T_GRID");

}


Vec2 Scene_Play::gridToMidPixel(int gridX, int gridY, std::shared_ptr<Entity> entity)
{
    sf::Vector2f size = entity->getComponent<CAnimation>().animation.m_sprite.getSize();
    Vec2 res;
    res.x = ( gridX * m_gridSize.x ) + size.x;
    res.y = ( gridY * m_gridSize.y ) + size.y;
    return res;
}

void Scene_Play::update()
{
    m_entityFact.update();

    if (!m_paused)
    {
        sMovement();
        sLifespan();
        sCollision();
    }
    sAnimation();
    sRender();
}


///////////////////////////////////////////////////
/////////  SYSTEMS   //////////////////////
///////////////////////////////////////////////////


void Scene_Play::sMovement()
{
    auto & pTransform = m_player->getComponent<CTransform>();
    auto & pInput = m_player->getComponent<CInput>();

    // set current pos as prev pos
    pTransform.prevPos = pTransform.pos;
    // than move it

    Vec2 pVelocity;

    if (pInput.left)
        pVelocity.x -= m_playerConfig.S;

    if (pInput.right)
        pVelocity.x += m_playerConfig.S;

    if (pInput.up)
    {
        pVelocity.y -= m_playerConfig.JUMP;
        pVelocity.y += m_playerConfig.GRAVITY;
    }

    if (pInput.down)
    {
        pVelocity.y += m_playerConfig.JUMP;
        pVelocity.y += m_playerConfig.GRAVITY;
    }

    // if bigger than max speed, limit it to max
    pVelocity.x = ( pVelocity.x > m_playerConfig.MAX_S ) ?
        m_playerConfig.MAX_S : pVelocity.x;

    pVelocity.y = ( pVelocity.y > m_playerConfig.MAX_S ) ?
        m_playerConfig.MAX_S : pVelocity.y;

    pVelocity.x = ( pVelocity.x < -m_playerConfig.MAX_S ) ?
        -m_playerConfig.MAX_S : pVelocity.x;

    pVelocity.y = ( pVelocity.y < -m_playerConfig.MAX_S ) ?
        -m_playerConfig.MAX_S : pVelocity.x;

    pTransform.velocity = pVelocity;

    // setting entity's scale.x to -1 => left
    // setting entity's scale.x to 1 => right

    for (auto e : m_entityFact.getEntities())
    {
        auto & eTransform = e->getComponent<CTransform>();
        eTransform.pos += eTransform.velocity;

    }
}

void Scene_Play::sLifespan()
{
}

void Scene_Play::sAnimation()
{
    auto & pState = m_player->getComponent<CState>();
    auto & pInput = m_player->getComponent<CInput>();
    auto & pTransform = m_player->getComponent<CTransform>();

    switch (pState.state)
    {
        case State::IDLE:
            if (pInput.right)
            {
                pTransform.scale.x = std::abs(pTransform.scale.x);
                m_player->addComponent<CAnimation>(m_game->assets().getAnimation("P_Walk"));
            }

            else if (pInput.left)
            {
                pTransform.scale.x = - std::abs(pTransform.scale.x);
                m_player->addComponent<CAnimation>(m_game->assets().getAnimation("P_Walk"));
            }
            break;

        case State::WALK:
            if (pInput.up)
                m_player->addComponent<CAnimation>(m_game->assets().getAnimation("P_Jump"), false);
            else if (pInput.attack)
                m_player->addComponent<CAnimation>(m_game->assets().getAnimation("P_Attack"));
            break;

    }


    // set animation of player based on CState
    // for each entity with anim call update
    // if animation not repeated, and ended, destroy it
}

void Scene_Play::sRender()
{
    m_game->m_window.clear();

    for (auto e : m_entityFact.getEntities())
    {
        m_game->m_window.draw(e->getComponent<CAnimation>().m_sprite)
    }

    m_game->m_window.display();
}

void Scene_Play::sCollision()
{
    // player / tile collisions and resolutions
    // resolve collision and update state
    for (auto p : m_entityFact.getEntities("player"))
    {
        auto & pTransform = p->getComponent<CTransform>();
        auto & pBorder = p->getComponent<CBBox>();
        // check to see if player has fallen down a hole
        if ( (pTransform.pos.y + pBorder.halfSize.y) > m_game->m_window.getSize().y)
        {
            p->destroy();
            // spawn player
        }

        // dont let player to move left side 
        if ( (pTransform.pos.x - pBorder.halfSize.x) < 0)
            pTransform.pos.x = pBorder.halfSize.x;


        // collisions with tiles
        for (auto t : m_entityFact.getEntities("tile"))
        {
            auto overlap = Physics::GetOverlap(p, t);
            if (overlap)
            {
                auto prevOverlap = Physics::GetPreviousOverlap(p, t);

                if (prevOverlap.y)
                    pTransform.pos.x = pTransform.prevPos.x;

                else if (prevOverlap.x)
                    pTransform.pos.y = pTransform.prevPos.y;

                else
                    pTransform.pos = pTransform.prevPos;
            }

        }


    }

    // kill enemies
    for (auto attack : m_entityFact.getEntities("attack"))
    {
        for (auto enemy : m_entityFact.getEntities("enemy"))
        {
            auto overlap = Physics::GetOverlap(attack, enemy);
            if (overlap)
            {

            }
        }

    }
}


void Scene_Play::sDoAction(const Action & action)
{
    auto pair = m_actionMap.find(action.code());
    if ( pair != m_actionMap.end() )
    {
        if ( action.type() == "START" )
        {
            if (pair->second == "JUMP")
                m_player->getComponent<CInput>().up = true;

            else if (pair->second == "LEFT")
                m_player->getComponent<CInput>().left = true;

            else if (pair->second == "DOWN")
                m_player->getComponent<CInput>().down = true;

            else if (pair->second == "RIGHT")
                m_player->getComponent<CInput>().right = true;

            else if (pair->second == "ATTACK")
                m_player->getComponent<CInput>().attack = true;

            else if (pair->second == "T_TEXTURE")
                m_drawTextures = !m_drawTextures;

            else if (pair->second == "T_COLLISION")
                m_drawCollision = !m_drawCollision;

            else if (pair->second == "T_GRID")
                m_drawGrid = !m_drawGrid;

            else if (pair->second == "QUIT")
                m_hasEnded = true;

            else if (pair->second == "PAUSE")
                m_paused = true;

        }

        else if ( action.type() == "END" )
        {
            if (pair->second == "JUMP")
                m_player->getComponent<CInput>().up = false;

            else if (pair->second == "LEFT")
                m_player->getComponent<CInput>().left = false;

            else if (pair->second == "DOWN")
                m_player->getComponent<CInput>().down = false;

            else if (pair->second == "RIGHT")
                m_player->getComponent<CInput>().right = false;

            else if (pair->second == "ATTACK")
                m_player->getComponent<CInput>().attack = false;

        }
    }
}

