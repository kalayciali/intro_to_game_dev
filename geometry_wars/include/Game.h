#pragma once

#include "Common.h"
#include "Entity.h"
#include "EntityManager.h"
#include "config.h"
#include <string>

struct PlayerConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V;
    float S;

    void set(std::ifstream &);
};

struct EnemyConfig
{
    int SR, CR, FB, OR, OG, OB, OT, VMIN, VMAX, L, SI;
    float SMIN, SMAX;

    void set(std::ifstream &);
};

struct BulletConfig
{
    int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L;
    float S;

    void set(std::ifstream &);
};

class Game
{

    uint m_seed() { static uint seed = 21; return seed; }
    std::string m_source_dir = RESOURCE_PATH;

    PlayerConfig m_P_config;
    EnemyConfig m_E_config;
    BulletConfig m_B_config;

    sf::RenderWindow m_window;
    EntityManager m_entity_fact;
    sf::Font m_font;
    sf::Text m_text;

    int m_current_frame = 0;
    int m_last_enemy_time = 0;
    int m_score = 0;
    bool m_running = true;
    bool m_paused = false;

    std::shared_ptr<Entity> m_player;


    // initialize the game state with config file
    void init(std::string config);

    void checkBorder(std::shared_ptr<Entity>);
    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnenmy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mouse_pos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

    Game();
    void run();
};
