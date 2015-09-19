
#include        "Map/ClassMap.hpp"

ClassMap::ClassMap() : ClassCase()
{
    m_begin = SMART(LnkCase)(new LnkCase(ALL, this));
    m_begin->set_pos(std::make_pair(0, 0));
    m_map.insert(boost::bimap<std::pair<int, int>, SMART(LnkCase)>::value_type(m_begin->get_pos(), m_begin));
}

ClassMap::~ClassMap()
{
}

void        ClassMap::add_obj(SMART(ObjectMap) obj)
{
    std::pair<int, int>     pos;
    LnkCase                 *lnk;
    boost::bimap<std::pair<int, int>, SMART(LnkCase)>::left_map::iterator  it;

    pos = obj->get_pos();
    pos.first += pos.first < 0 ? -m_size / 10 : m_size / 10;
    pos.second += pos.second < 0 ? -m_size / 10  : m_size / 10;
    pos.first = pos.first / (m_size / 5);
    pos.second = pos.second / (m_size / 5);
    if ((it = m_map.left.find(pos)) != m_map.left.end())
        lnk = it->second.get();
    else
        lnk = make_lnk(pos);
    if (!lnk->get_case())
    {
        if (m_size > 150)
            lnk->set_case(new ClassMap());
        else
            lnk->set_case(new ClassCase());
        lnk->get_case()->set_lnk(lnk);
        lnk->get_case()->set_size(m_size / 5);
        cross_lnk(lnk, LEFT);
        cross_lnk(lnk, RIGHT);
        cross_lnk(lnk, UP);
        cross_lnk(lnk, DOWN);
    }
    ClassCase::add_obj(obj);
    lnk->get_case()->add_obj(obj);
}

void        ClassMap::cross_lnk(LnkCase *lnk, LnkDir dir)
{
    std::pair<int, int>         tmp;
    LnkCase                     *cross;
    LnkCase                     *tmpLnk;
    bool                        first;
    LnkDir                      tmpdir;

    tmp.first = dir > 1 ? lnk->get_pos().first : 0;
    tmp.second = dir < 2 ? lnk->get_pos().second : 0;
    cross = m_map.left.find(tmp)->second.get();
    first = true;
    while ((cross = cross->get_dir(dir)))
    {
        tmp.first = dir > 1 ? cross->get_pos().first : lnk->get_pos().first;
        tmp.second = dir < 2 ? cross->get_pos().second : lnk->get_pos().second;
        tmpdir = (dir > 1 ? (lnk->get_pos().second > cross->get_pos().second ? DOWN : UP) :
                         (lnk->get_pos().first < cross->get_pos().first ? LEFT : RIGHT));
        tmpLnk = cross->get_next(tmpdir, tmp, first, false);
        if (first && tmpLnk != lnk->get_dir(dir) && tmpLnk != lnk)
        {
            tmpLnk->set_dir(dir, lnk->get_dir(dir));
            if (lnk->get_dir(dir))
                lnk->get_dir(dir)->set_dir(INV_DIR(dir), tmpLnk);
            tmpLnk->set_dir(INV_DIR(dir), lnk);
            lnk->set_dir(dir, tmpLnk);
        }
        first = false;
        return ;
    }
}

LnkCase     *ClassMap::make_lnk(std::pair<int, int> &pos)
{
    LnkCase                         *lnk[2];
    LnkCase                         *res;
    LnkDir                          dir[2];
    int                             it;

    for (it = 0; it < 2; it++)
    {
        dir[it] = !it ? (pos.first > 0 ? RIGHT : LEFT) : (pos.second > 0 ? DOWN : UP);
        lnk[it] = m_begin->get_next(dir[it], pos, true, false);
        dir[it] = it ? (pos.first > 0 ? RIGHT : LEFT) : (pos.second > 0 ? DOWN : UP);
        lnk[it] = lnk[it]->get_next(dir[it], pos, false, false);
        if (lnk[it]->get_pos().first == pos.first && lnk[it]->get_pos().second == pos.second)
            return (lnk[it]);
    }
    if (pos.first == 0 || pos.second == 0)
        res = new LnkCase(pos.first == 0 ? dir[0] : dir[1], this);
    else
        res = new LnkCase(NONE, this);
    res->set_pos(pos);
    insert(res);
    for (it = 0; it < 2; it++)
    {
        res->set_dir(INV_DIR(dir[it]), lnk[it]);
        res->set_dir(dir[it], lnk[it]->get_dir(dir[it]));
        if (lnk[it]->get_dir(dir[it]))
            lnk[it]->get_dir(dir[it])->set_dir(INV_DIR(dir[it]), res);
        lnk[it]->set_dir(dir[it], res);
    }
    return (res);
}

void                    ClassMap::insert(LnkCase *lnk)
{
    SMART(LnkCase)      add;

    add = SMART(LnkCase)(lnk);
    m_map.insert(boost::bimap<std::pair<int, int>, SMART(LnkCase)>::value_type(lnk->get_pos(), add));
}

SMART(ObjectMap)        ClassMap::remove_object(ObjectMap *obj)
{
    SMART(ObjectMap)        res;
    LnkCase                 *mycase;

    mycase = obj->get_cases()->get_lnk();
    while (mycase && mycase->get_case() != this)
    {
        mycase->get_case()->remove_obj(obj);
        mycase = mycase->get_map()->get_lnk();
    }
    res = ClassCase::remove_obj(obj);
    return (res);
}

void        ClassMap::move_object(ObjectMap *obj)
{
    SMART(ObjectMap)    tmp;

    tmp = remove_object(obj);
    add_obj(tmp);
}

void        ClassMap::clean()
{
    MAP::iterator  it;
    MAP::iterator  rm;
    int            i;

    it = m_map.begin();
    while (it != m_map.end())
    {
        if (CAST(ClassMap*)(it->right->get_case()))
            CAST(ClassMap*)(it->right->get_case())->clean();
        if (it->right->get_case() && !it->right->get_case()->get_obj().size())
        {
            delete it->right->get_case();
            it->right->set_case(NULL);
        }
        i = 10;
        if (!it->right->get_case() && it->right->get_pos().first != 0 && it->right->get_pos().second != 0)
        {
            for (i = 0; i < 4; i++)
            {
                if (it->right->get_dir((LnkDir)i) && it->right->get_dir((LnkDir)i)->get_case())
                    i = 10;
            }
        }
        if (i < 10)
        {
            rm = it++;
            rm->right->remove();
            m_map.erase(rm);
        }
        else
            it++;
    }
}

LEFT_MAP::iterator              ClassMap::get_begin()
{
    return (m_map.left.begin());
}

LEFT_MAP::iterator              ClassMap::get_end()
{
    return (m_map.left.end());
}

void                            ClassMap::get_move_line(MovableLine *move, ClassCase *from, Object *obj)
{
    ClassCase::get_move_line(move, from, obj);
}
