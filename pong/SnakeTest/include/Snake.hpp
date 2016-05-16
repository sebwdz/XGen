#ifndef SNAKE_HPP
#define SNAKE_HPP

#include            "Cell/Brain.hpp"
#include            "include/Map.hpp"

class Snake
{
public:
    Snake();

    std::pair<float, float>     const   &getPos() const;
    float                               getAngle() const;
    void                                changeDir(bool, float = 20);
    void                                view(Map &map, Map::CaseType find);
    void                                exec(Map &map, bool real = false);
    void                                setMove(char);
private:
    Brain           m_brain;
    std::pair<float, float> m_pos;
    std::pair<float, float> m_dir;
    float                   m_angle;
    SMART(GeneticalNode)    m_input;
    SMART(GeneticalNode)    m_output;
    SMART(GeneticalNode)    m_good;
    SMART(GeneticalNode)    m_bad;
    unsigned int            m_lastEat;
    char                    m_mv;
};

#endif // SNAKE_HPP
