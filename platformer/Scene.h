#include "Common.h"
#include "GameEngine.h"
#include "EntityManager.h"
#include "Action.h"
#include <string>

// abstract base class
class Scene
{
protected:

    GameEngine * m_game; 
    EntityManager m_entityFact;
    size_t m_currentFrame;
    std::map<int, std::string> m_actionMap;
    bool m_paused;
    bool m_hasEnded;

    Scene(GameEngine * game);

    virtual void sRender() = 0;
    virtual void update() = 0;

public:

    void registerAction(int key, const std::string & command);
    void simulate(int);
    virtual void sDoAction(const Action &) = 0; 
};
