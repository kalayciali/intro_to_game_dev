#include "Scene_Play.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <memory>

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

            fin >> animName;
            fin >> m_playerConfig.X >> m_playerConfig.Y;
            fin >> m_playerConfig.CX >> m_playerConfig.CY;
            fin >> m_playerConfig.S >> m_playerConfig.JUMP;
            fin >> m_playerConfig.MAX_S >> m_playerConfig.GRAVITY;

            auto player = m_entityFact.addEntity("player");

            player->addComponent<CAnimation>(m_game->assets().getAnimation(animName));
            player->addComponent<CInput>();
            player->addComponent<CTransform>(
                    gridToMidPixel(m_playerConfig.X, m_playerConfig.Y, player));
            player->addComponent<CBBox>({ m_playerConfig.CX, m_playerConfig.CY });
            player->addComponent<CGravity>( m_playerConfig.GRAVITY );
            player->addComponent<CState>("idle");
            m_player = player;

        }
    }


    if (brick->getComponent<CAnimation>().animation.getName() == "brick")
    {

    }

    // components are now returned as references, so use references
    // auto & transform1 = entity->get<CTransform>()
}

void Scene_Play::init(const std::string & levelPath)
{
    loadLevel(levelPath);


    registerAction(sf::Keyboard::W, &m_player->getComponent<CInput>().up);
    registerAction(sf::Keyboard::A, &m_player->getComponent<CInput>().left);
    registerAction(sf::Keyboard::S, &m_player->getComponent<CInput>().down);
    registerAction(sf::Keyboard::D, &m_player->getComponent<CInput>().right);
    registerAction(sf::Keyboard::Space, &m_player->getComponent<CInput>().attack);

    registerAction(sf::Keyboard::P, &m_player->getComponent<CInput>().pause);
    registerAction(sf::Keyboard::Escape, &m_player->getComponent<CInput>().quit);
    registerAction(sf::Keyboard::T, &m_player->getComponent<CInput>().toggleTexture);
    registerAction(sf::Keyboard::C, &m_player->getComponent<CInput>().toggleCollision);
    registerAction(sf::Keyboard::G, &m_player->getComponent<CInput>().toggleGrid);

}


Vec2 Scene_Play::gridToMidPixel(int gridX, int gridY, std::shared_ptr<Entity> entity)
{
    sf::Vector2f size = entity->getComponent<CAnimation>().animation.m_sprite.getSize();
    Vec2 res;
    res.x = ( gridX * m_gridSize.x ) + size.x;
    res.y = ( gridY * m_gridSize.y ) + size.y;
    return res;
}


void Scene_Play::sMovement()
{
    auto & pTransform = m_player->getComponent<CTransform>();
    auto & pInput = m_player->getComponent<CInput>();

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

    for (auto e : m_entityFact.getEntities())
    {
        auto & eTransform = e->getComponent<CTransform>();
        eTransform.pos += eTransform.velocity;

    }

}

void Scene_Play::sDoAction(const Action & action) {
    if ( m_actionMap.find(action.code()) != m_actionMap.end() )
    {
        if (action.type() == "START")
            (* m_actionMap[action.code()] ) = true;

        else if (action.type() == "END")
            (* m_actionMap[action.code()] ) = false;
}

