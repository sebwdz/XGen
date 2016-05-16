
#include    <cstdlib>
#include    <cmath>
#include    <iostream>
#include    "include/Map.hpp"

Map::Map()
{
    m_wall._type = Map::WALL;
    m_wall._view = false;
    m_size.first = 50;
    m_size.second = 50;
    m_cases.resize(50 * 50, Case());
    for (unsigned int it = 0; it < 50 * 50; it++)
    {
        if (it / 50 == 0 || it / 50 == 49 ||
                !(it % 50) || !((it + 1) % 50) || random() % 2000 > 1990)
            m_cases[it]._type = WALL;
        else
            m_cases[it]._type = random() % 100 > 1 ? EMPTY : FOOD;
        m_cases[it]._view = false;
    }
}

std::pair<int, int> const &Map::getSize() const
{
    return (m_size);
}

Map::Case const                        &Map::getCase(std::pair<int, int> const& pos) const
{
    int                     it;

    it = pos.second * m_size.first + pos.first;
    if (it > m_size.first * m_size.second)
        return (m_wall);
    return (m_cases[it]);
}

Map::Case                        &Map::getCase(std::pair<int, int> const& pos)
{
    int                     it;

    it = pos.second * m_size.first + pos.first;
    if (it > m_size.first * m_size.second)
        return (m_wall);
    return (m_cases[it]);
}

float                         Map::view(float angle, std::pair<float, float> pos, CaseType find)
{
    std::pair<float, float>     dir;
    std::pair<float, float>     cross;
    std::pair<float, float>     tmp;
    int                it;
    int                x;
    float               res;

    dir.first = std::cos(angle * 3.14 / 180);
    dir.second = std::sin(angle * 3.14 / 180);
    cross.first = std::cos((angle + 98) * 3.14 / 180);
    cross.second = std::sin((angle + 98) * 3.14 / 180);
    res = 0;
    for (it = 0; it < 12; it++)
    {
        pos.first += dir.first;
        pos.second += dir.second;
        for (x = -it * 0.4; x < it * 0.4 + 1; x++)
        {
            tmp = pos;
            tmp.first += cross.first * x;
            tmp.second += cross.second * x;
            if (getCase(tmp)._type == find)
                res += 5.0 / (it + 1);
            getCase(tmp)._view = true;
        }
    }
    return (res);
}
