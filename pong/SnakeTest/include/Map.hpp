#ifndef MAP_HPP
#define MAP_HPP

#include    <vector>

class Map
{
public:
    enum    CaseType
    {
        EMPTY,
        FOOD,
        WALL,
    };

    struct Case
    {
        CaseType    _type;
        bool        _view;
    };

public:
    Map();

    std::pair<int, int> const &getSize() const;
    Case                        &getCase(std::pair<int, int> const&);
    Case const                  &getCase(std::pair<int, int> const&) const;
    float                       view(float angle, std::pair<float, float> pos, CaseType);

private:
    std::pair<int, int> m_size;
    std::vector<Case>   m_cases;
    Case                m_wall;
};

#endif // MAP_HPP
