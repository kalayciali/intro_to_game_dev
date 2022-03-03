#include <string>

class Action
{
    std::string m_name;
    int m_code;
    std::string m_type; // start or end

public:

    Action(const std::string & name, int code, const std::string & type = "START")
        : m_name(name), m_type(type), m_code(code){  }

    const std::string & name() const { return m_name; }
    const std::string & type() const { return m_type; }
    int code() const { return m_code; }
    void setType(const std::string & type) { m_type = type; }
};
