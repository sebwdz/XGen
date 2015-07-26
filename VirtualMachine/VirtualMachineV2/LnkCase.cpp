
#include        "ClassMap.hpp"

LnkCase::LnkCase()
{

}

LnkCase::~LnkCase()
{

}

void        LnkCase::add_obj(SMART(ObjectMap) obj, std::pair<int, int> &pos, LnkDir dir)
{
    std::pair<int, int>     tmp;
    ClassCase               *oth;
    bool                    ok;

    if ((oth = CAST(ClassCase*)(m_dir[dir].get())))
        ok = (pos.first > oth->get_pos().first && dir == RIGHT) || (pos.second > oth->get_pos().second && dir == DOWN);
    if (!m_dir[dir] || ok)
    {

    }
    else if (oth)
    {

    }
}

void        LnkCase::set_dir(LnkDir dir, SMART(LnkCase) lnk)
{
    m_dir[dir] = lnk;
}

void        LnkCase::remove()
{
    int     oth;
    int     it;

    for (it = 0; it < 4; it++)
    {
        oth = it % 2 ? it - 1 : it + 1;
        if (m_dir[it])
            m_dir[it]->set_dir((LnkDir)oth, m_dir[oth]);
    }
}

SMART(LnkCase)     LnkCase::get_dir(LnkDir dir)
{
    return (m_dir[dir]);
}
