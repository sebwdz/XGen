
#include        "Map/ClassMap.hpp"

ClassMap::ClassMap() : ClassCase()
{
    m_begin = new LnkCase(ALL, this);
    m_begin->set_pos(std::make_pair(0, 0));
}

ClassMap::~ClassMap()
{
  //m_begin->remove(true);
  delete m_begin;
}

void        ClassMap::add_obj(Object *obj)
{
    std::pair<int, int>     pos;
    LnkCase                 *lnk;

    pos = obj->get_pos();
    pos.first += pos.first < 0 ? -m_size / 10 : m_size / 10;
    pos.second += pos.second < 0 ? -m_size / 10  : m_size / 10;
    pos.first = pos.first / (m_size / 5);
    pos.second = pos.second / (m_size / 5);
    lnk = make_lnk(pos);
    if (!lnk->get_case())
    {
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
    cross = make_lnk(tmp);
    first = true;
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
    it = 0;
    while (it < 2)
    {
        res->set_dir(INV_DIR(dir[it]), lnk[it]);
        res->set_dir(dir[it], lnk[it]->get_dir(dir[it]));
        if (lnk[it]->get_dir(dir[it]))
            lnk[it]->get_dir(dir[it])->set_dir(INV_DIR(dir[it]), res);
        lnk[it]->set_dir(dir[it], res);
        it+=1;
    }
    return (res);
}

void                    ClassMap::remove_object(ObjectMap *obj)
{
    SMART(ObjectMap)        res;
    LnkCase                 *mycase;

    mycase = obj->get_cases()->get_lnk();
    mycase->get_case()->remove_obj(obj);
    obj->set_case(NULL);
    ClassCase::remove_obj(obj);
    if (mycase->get_case()->get_obj().size() < 1)
      {
        delete mycase->get_case();
        mycase->set_case(NULL);
        if (mycase->check_remove())
          {
              mycase->remove();
              delete mycase;
          }
      }
}
