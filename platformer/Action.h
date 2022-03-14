#include <string>
#include "Vec2.h"

class Action
{
    std::string m_name = "NONE";
    int m_code = -1;
    std::string m_type = "NONE"; // start or end
    Vec2 m_pos = Vec2(0, 0);

public:

    // action for mouse move events
    Action(int code, const std::string & name = "KEY", const std::string & type = "START")
        :  m_code(code), m_name(name), m_type(type) {  }


    const std::string & type() const { return m_type; }
    const std::string & name() const { return m_name; }
    const Vec2 & pos() const { return m_pos; }
    int code() const { return m_code; }

    void setType(const std::string & type) { m_type = type; }
    void setPos(float x, float y) { m_pos.x = x; m_pos.y = y; }
};
