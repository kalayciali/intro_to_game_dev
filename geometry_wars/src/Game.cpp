#include "Game.h"
#include <SFML/Graphics/Color.hpp>
#include <ctime>
#include <iostream>
#include <ostream>

void PlayerConfig::set(std::ifstream & fin)
{
    fin >> SR >> CR >> S >> FR >> FG >> FB;
    fin >> OR >> OG >> OB >> OT >> V;
}

void EnemyConfig::set(std::ifstream & fin)
{
    fin >> SR >> CR >> SMIN >> SMAX >> OR >> OG >> OB;
    fin >> OT >> VMIN >> VMAX >> L >> SI;
}

void BulletConfig::set(std::ifstream & fin)
{
    fin >> SR >> CR >> S >> FR >> FG >> FB;
    fin >> OR >> OG >> OB >> OT >> V >> L;
}

Game::Game()
{
    init(m_source_dir);
}

void Game::init(std::string path)
{
    std::ifstream fin(path + "config.txt");
    std::string input_type;
    srand(m_seed());

    {
        // set window
        int w_width, w_height, antialias, frate, fullscreen; 
        fin >> input_type >> w_width >> w_height;
        fin >> frate >> fullscreen >> antialias;

        sf::ContextSettings settings;
        settings.antialiasingLevel = antialias;

        if (fullscreen)
            m_window.create(sf::VideoMode(w_width, w_height), "Geometry Wars", 
                sf::Style::Fullscreen, settings);
        else
            m_window.create(sf::VideoMode(w_width, w_height), "Geometry Wars", 
                sf::Style::Default, settings);

        m_window.setFramerateLimit(frate);
    }

    {
        // get font
        std::string font_file;
        int t_size;
        int clrR, clrG, clrB;

        fin >> input_type >> font_file;

        if (!m_font.loadFromFile(path + font_file))
        {
            // if we can't load the font, print an error and exit
            std::cerr << "Could not load font\n";
            exit(-1);
        } else
        {
            fin >> t_size >> clrR >> clrG >> clrB;
        }

        sf::Color f_color(clrR, clrG, clrB);
        m_text.setCharacterSize(t_size);
        m_text.setFont(m_font);
        m_text.setFillColor(f_color);
    }

    while (fin >> input_type)
    {
        if (input_type == "Player") 
            m_P_config.set(fin);
        else if (input_type == "Enemy")
            m_E_config.set(fin);
        else 
            m_B_config.set(fin);
    }

    spawnPlayer();
}


void Game::spawnPlayer()
{
    auto entity = m_entity_fact.addEntity("player");
    auto w_size = m_window.getSize();

    entity->c_transform = std::make_shared<CTransform>(
            Vec2(w_size.x / 2.f, w_size.y / 2.f),
            Vec2(0.f, 0.f), 
            1.f
            );

    entity->c_shape = std::make_shared<CShape>(
            m_P_config.SR, 
            m_P_config.V,
            sf::Color(m_P_config.FR, m_P_config.FG, m_P_config.FB),
            sf::Color(m_P_config.OR, m_P_config.OG, m_P_config.OB),
            m_P_config.OT
            );

    entity->c_collision = std::make_shared<CCollision>(
            m_P_config.CR
            );

    entity->c_input = std::make_shared<CInput>();
    m_player = entity;
}

void Game::spawnEnenmy()
{
    auto window = m_window.getSize();
    ptr<Entity> enemy = m_entity_fact.addEntity("enemy");

    //transform
    int x_max = window.x - m_E_config.CR;
    int y_max = window.y - m_E_config.CR;

    int x_diff = 1 + x_max - m_E_config.CR;
    int y_diff = 1 + y_max - m_E_config.CR;


    Vec2 pos;
    pos.x = ( rand() % x_diff ) + m_E_config.CR;
    pos.y = ( rand() % y_diff ) + m_E_config.CR;

    Vec2 velocity;
    // cast it to int
    int speed_diff = m_E_config.SMAX - m_E_config.SMIN;


    velocity.x = ( rand() % speed_diff ) + m_E_config.SMIN;
    velocity.y = ( rand() % speed_diff ) + m_E_config.SMIN;

    enemy->c_transform = std::make_shared<CTransform>(
            pos, velocity, 1.f );

    // shape
    int v_diff = m_E_config.VMAX - m_E_config.VMIN;
    int vertices  = ( rand() % v_diff ) + m_E_config.VMIN;

    enemy->c_shape = std::make_shared<CShape>(
            m_E_config.SR, 
            vertices,
            sf::Color(rand() % 256, rand() % 256, rand() % 256),
            sf::Color(m_E_config.OR, m_E_config.OG, m_E_config.OB),
            m_E_config.OT
            );

    enemy->c_collision = std::make_shared<CCollision>(
            m_E_config.CR
            );
    enemy->c_score = std::make_shared<CScore>(
            100 );
}


void Game::spawnSmallEnemies(ptr<Entity> e)
{
    // when spawning enemies, we have to read values 
    // from entity killed
    // set each small enemy half the size with same color 
    // small enemies worth double points
    int vertices = e->c_shape->circle.getPointCount();
    auto color = e->c_shape->circle.getFillColor();
    auto speed = e->c_transform->velocity.magnitude();
    auto pos = e->c_transform->pos;
    float piece = 2.f / vertices;
    int score = e->c_score->score;

    for (int i = 0; i < vertices; i++)
    {
        float angle = i * piece * M_PI;
        auto small_enemy = m_entity_fact.addEntity("enemy");

        small_enemy->c_score = std::make_shared<CScore>(2 * score);

        small_enemy->c_transform = std::make_shared<CTransform>(
                pos, 
                Vec2(speed * std::cos(angle), speed * std::sin(angle)),
                1.f
                );

        small_enemy->c_shape = std::make_shared<CShape>(
                m_E_config.SR / 2, 
                vertices,
                color,
                sf::Color(m_E_config.OR, m_E_config.OG, m_E_config.OB),
                m_E_config.OT
                );
        small_enemy->c_collision = std::make_shared<CCollision>(
                m_E_config.CR / 2
                );
        small_enemy->c_lifespan = std::make_shared<CLifespan>(
                m_E_config.L,
                m_current_frame
                );
    }
}

void Game::spawnBullet(ptr<Entity> entity, const Vec2 & target)
{
    auto pos = entity->c_transform->pos;
    const float angle = std::atan2(target.y - pos.y, target.x - pos.x);

    pos.x += entity->c_shape->circle.getRadius() * cos(angle);
    pos.y += entity->c_shape->circle.getRadius() * sin(angle);

    auto bullet = m_entity_fact.addEntity("bullet");

    bullet->c_transform = std::make_shared<CTransform>(
            pos, 
            Vec2(m_B_config.S * std::cos(angle), m_B_config.S * std::sin(angle)),
            1.f
            );

    bullet->c_shape = std::make_shared<CShape>(
            m_B_config.SR, 
            m_B_config.V,
            sf::Color(m_B_config.FR, m_B_config.FG, m_B_config.FB),
            sf::Color(m_B_config.OR, m_B_config.OG, m_B_config.OB),
            m_B_config.OT
            );
    bullet->c_collision = std::make_shared<CCollision>(
            m_B_config.CR
            );
    bullet->c_lifespan = std::make_shared<CLifespan>(
            m_B_config.L,
            m_current_frame
            );

}

void Game::spawnSpecialWeapon(ptr<Entity> entity)
{
}

//////////////////////////////////////////////////
// SYSTEMS ////////////////////////
//////////////////////////////////////////////////

void Game::sMovement()
{
    Vec2 player_vel;

    float diff = m_P_config.S - m_P_config.S * std::cos(0.25f);

    if (m_player->c_input->left) 
        player_vel.x -= m_P_config.S;
    if (m_player->c_input->right)
        player_vel.x += m_P_config.S;

    if (m_player->c_input->up)
        player_vel.y -= m_P_config.S;
    if (m_player->c_input->down)
        player_vel.y += m_P_config.S;

    if (m_player->c_input->right && m_player->c_input->up)
    {
        player_vel.x -= diff;
        player_vel.y += diff;
    }

    if (m_player->c_input->left && m_player->c_input->up)
    {
        player_vel.x += diff;
        player_vel.y += diff;
    }

    if (m_player->c_input->left && m_player->c_input->down)
    {
        player_vel.x += diff;
        player_vel.y -= diff;
    }

    if (m_player->c_input->right && m_player->c_input->down)
    {
        player_vel.x -= diff;
        player_vel.y -= diff;
    }

    m_player->c_transform->velocity = player_vel;

    for (auto e : m_entity_fact.getEntities())
    {
        e->c_transform->pos += e->c_transform->velocity;
    }

}

void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_running = false;

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                    m_player->c_input->up = true;
                    break;
                case sf::Keyboard::A:
                    m_player->c_input->left = true;
                    break;
                case sf::Keyboard::S:
                    m_player->c_input->down = true;
                    break;
                case sf::Keyboard::D:
                    m_player->c_input->right = true;
                    break;
                case (sf::Keyboard::P || sf::Keyboard::Menu):
                    m_paused = !m_paused;
                default:
                    break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                    m_player->c_input->up = false;
                    break;
                case sf::Keyboard::A:
                    m_player->c_input->left = false;
                    break;
                case sf::Keyboard::S:
                    m_player->c_input->down = false;
                    break;
                case sf::Keyboard::D:
                    m_player->c_input->right = false;
                    break;
                default:
                    break;
            }

        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            Vec2 mouse(event.mouseButton.x, event.mouseButton.y);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_player->c_input->shoot = true;
                spawnBullet(m_player, mouse);
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                // spawnSpecialWeapon(m_player, mouse);
            }
        }
            
    }
}

void Game::sLifespan()
{
    for (auto e : m_entity_fact.getEntities())
    {
        if (e->c_lifespan)
        {
            int end_time = e->c_lifespan->currentFrame();

            if (end_time < m_current_frame)
            {
                e->destroy();
                continue;
            }

            auto color = e->c_shape->circle.getFillColor();
            sf::Color newColor(color.r, color.g, color.b, color.a - 10);
            e->c_shape->circle.setFillColor(newColor);
        }
    }

}

void Game::sRender()
{
    m_window.clear();

    for (auto e : m_entity_fact.getEntities())
    {
        sf::Vector2f newPos(e->c_transform->pos.x, e->c_transform->pos.y);
        e->c_shape->circle.setPosition(newPos);
        e->c_shape->circle.rotate(e->c_transform->angle);
        m_window.draw(e->c_shape->circle);
    }

    std::string text("Score " + std::to_string(m_score));
    m_text.setFont(m_font);
    m_text.setString(text);
    m_window.draw(m_text);

    m_window.display();
}

void Game::sEnemySpawner()
{
    int frame_passed = m_current_frame - m_last_enemy_time;
    if (frame_passed > m_E_config.SI)
    {
        spawnEnenmy();
        m_last_enemy_time = m_current_frame;
    }
}

void Game::checkBorder(ptr<Entity> e)
{
    auto window = m_window.getSize();

    float radius = e->c_collision->radius;
    auto pos = e->c_transform->pos;
    auto velocity = e->c_transform->velocity;

    if ((pos.x + radius >= window.x) && (velocity.x > 0))
        e->c_transform->velocity.x = -velocity.x;

    if ((pos.x < radius) && (velocity.x < 0))
        e->c_transform->velocity.x = -velocity.x;

    if ((pos.y + radius >= window.y) && (velocity.y > 0))
        e->c_transform->velocity.y = -velocity.y;

    if ((pos.y < radius) && (velocity.y < 0))
        e->c_transform->velocity.y = -velocity.y;
}


void Game::sCollision()
{

    for (auto p : m_entity_fact.getEntities("player"))
    {
        checkBorder(p);

        for (auto e : m_entity_fact.getEntities("enemy"))
        {

            float dist = p->c_transform->pos.dist(e->c_transform->pos);

            if ( ( p->c_collision->radius + e->c_collision->radius ) >= dist)
            {
                p->destroy();
                m_score -= e->c_score->score;
                spawnPlayer();
            }

            checkBorder(e);
        }

    }

    for (auto b : m_entity_fact.getEntities("bullet"))
    {
        for (auto e : m_entity_fact.getEntities("enemy"))
        {
            float dist = b->c_transform->pos.dist(e->c_transform->pos);

            if ( ( b->c_collision->radius + e->c_collision->radius ) >= dist)
            {
                b->destroy();
                e->destroy();

                if (!e->c_lifespan)
                    spawnSmallEnemies(e);

                m_score += e->c_score->score;
            }

        }
    }


}

// main loop of game
void::Game::run()
{
    while (m_running)
    {
        // update entities at the start of the frame
        m_entity_fact.update();
        sLifespan();

        if (!m_paused)
        {
            sEnemySpawner();
            sMovement();
        }

        sCollision();
        sUserInput();
        sRender();

        m_current_frame++;
    }
}
