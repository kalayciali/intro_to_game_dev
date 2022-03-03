#include "Common.h"
#include "GameEngine.h"
#include "EntityManager.h"
#include "Action.h"

// abstract base class
class Scene
{
protected:

    GameEngine * m_game; 
    EntityManager m_entityFact;
    size_t m_currentFrame;
    std::map<int, bool> m_actionMap;
    bool m_paused;
    bool m_hasEnded;

    Scene(GameEngine * game);

    virtual void update() = 0;
    virtual void sRender() = 0;

public:

    void registerAction(int key, bool * input);
    void simulate(int);
    virtual void sDoAction(const Action &) = 0; 
};
