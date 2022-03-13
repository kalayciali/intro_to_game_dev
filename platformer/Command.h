#include "Entity.h"

class Command
{
protected:
    std::string m_type;

public:

    virtual ~Command() {}
    virtual void execute(Entity & e) = 0;
    virtual void setType(const std::string & type) { m_type = type; }
};

class OnUp : public Command
{
public:
    void execute(Entity & e);
};

class OnDown : public Command
{
public: void execute(Entity & e);
};

class OnRight : public Command
{
public:
    void execute(Entity & e);
};

class OnLeft : public Command
{
public:
    void execute(Entity & e);
};

class OnPause : public Command
{
public:
    void execute(Entity & e);
};

