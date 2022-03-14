#include "Common.h"
#include "GameEngine.h"
#include "EntityManager.h"
#include "Action.h"
#include <string>
#include <functional>

// abstract base class
class Scene
{

protected:

    GameEngine * m_game;
    EntityManager m_entityFact;
    size_t m_currentFrame;
    // keyboard and mouse enums are basic enums
    std::map<int, std::function<void(Action)>>  m_keyToCommand;
    std::map<int, std::function<void(Action)>>  m_mouseToCommand;

    bool m_paused;
    bool m_hasEnded;

    Scene(GameEngine * game)
        : m_game(game), m_currentFrame(0),
        m_paused(false), m_hasEnded(false) {}

    virtual void sRender() = 0;
    virtual void update() = 0;

public:


    void registerCommand(int key, std::function<void(Action)>, const std::string & = "KEY");
    void simulate(int);
    virtual void sDoAction(const Action & action) = 0;
};

