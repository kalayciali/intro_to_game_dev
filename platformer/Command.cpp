#include "Command.h"

void OnUp::execute(Entity & e)
{
    if (m_type == "START")
        e.getComponent<CInput>().up = true;
    else if (m_type == "END")
        e.getComponent<CInput>().up = false;
}

void OnDown::execute(Entity & e)
{
    if (m_type == "START")
        e.getComponent<CInput>().down = true;
    else if (m_type == "END")
        e.getComponent<CInput>().down = false;
}

void OnRight::execute(Entity & e)
{
    if (m_type == "START")
        e.getComponent<CInput>().right = true;
    else if (m_type == "END")
        e.getComponent<CInput>().right = false;
}

void OnLeft::execute(Entity & e)
{
    if (m_type == "START")
        e.getComponent<CInput>().left = true;
    else if (m_type == "END")
        e.getComponent<CInput>().left = false;
}

void OnPause::execute(Entity & e)
{
    if (m_type == "START")
        e.getComponent<CInput>().left = true;
    else if (m_type == "END")
        e.getComponent<CInput>().left = false;
};

