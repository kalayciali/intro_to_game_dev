#include "Entity.h"
#include "Action.h"

#include <iostream>
#include <functional>

std::function<void(void)> closureWrapper1(const Action & action)
{
    int x = 10;
    return [x](){std::cout << "Value in the closure: " << x << std::endl;};
}

class Command
{
    std::string m_name;
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

