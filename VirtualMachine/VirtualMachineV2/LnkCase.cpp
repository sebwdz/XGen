
#include        "ClassMap.hpp"

LnkCase::LnkCase(bool border)
{
    m_case = NULL;
    m_pos.first = 0;
    m_pos.second = 0;
    m_border = border;
    m_dir[0] = NULL;
    m_dir[1] = NULL;
    m_dir[2] = NULL;
    m_dir[3] = NULL;
}

LnkCase::~LnkCase()
{
    delete m_case;
}

void        LnkCase::add_obj(SMART(ObjectMap) obj, std::pair<int, int> &pos, LnkDir dir, int turn)
{
    std::pair<int, int>     tmp;
    LnkCase                 *lnk;

    if (pos == m_pos && !m_border)
    {
        if (!m_case)
            m_case = new ClassCase();
        m_case->add_obj(obj);
        return ;
    }
    if ((!m_dir[dir] || m_dir[dir]->m_border) || tmp.first)
    {
        lnk = new LnkCase(false);
        lnk->set_dir((LnkDir)(dir % 2 ? dir - 1 : dir + 1), this);
        lnk->set_dir(dir, m_dir[dir]);
        if (m_dir[dir])
            m_dir[dir]->set_dir((LnkDir)(dir % 2 ? dir - 1 : dir + 1), lnk);
        m_dir[dir] = lnk;
        tmp.first = dir == LEFT || dir == RIGHT ? pos.first : m_pos.first;
        tmp.second = dir == UP || dir == DOWN ? pos.second : m_pos.second;
        lnk->set_pos(tmp);
        if (!turn)
        {
            if (dir == LEFT || dir == RIGHT)
                dir = pos.second > m_pos.second ? DOWN : UP;
            else
                dir = pos.first > m_pos.first ? RIGHT : LEFT;
            lnk->add_obj(obj, pos, dir, 1);
            return ;
        }
    }
    if (m_dir[dir])
        m_dir[dir]->add_obj(obj, pos, dir, turn);
}

void        LnkCase::set_pos(std::pair<int, int> pos)
{
    m_pos = pos;
}

void        LnkCase::set_dir(LnkDir dir,LnkCase *lnk)
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

LnkCase     *LnkCase::get_dir(LnkDir dir)
{
    return (m_dir[dir]);
}

std::pair<int, int>     &LnkCase::get_pos()
{
    return (m_pos);
}
