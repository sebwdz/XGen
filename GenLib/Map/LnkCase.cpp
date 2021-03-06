
#include        "Map/ClassMap.hpp"

LnkCase::LnkCase(LnkDir border, ClassMap *map)
{
  m_case = NULL;
  m_pos.first = 0;
  m_pos.second = 0;
  m_border = border;
  m_dir[0] = NULL;
  m_dir[1] = NULL;
  m_dir[2] = NULL;
  m_dir[3] = NULL;
  m_map = map;
}

LnkCase::~LnkCase()
{
  delete m_case;
}

LnkCase     *LnkCase::get_next(LnkDir dir, std::pair<int, int> &pos, bool create, bool cross)
{
  LnkCase                 *lnk;
  std::pair<int, int>     tmp;

  if ((dir > 1 && m_pos.first == pos.first) ||
      (dir < 2 && m_pos.second == pos.second))
    return (this);
  if (!m_dir[dir] || (((dir == RIGHT && m_dir[dir]->get_pos().first > pos.first) ||
                       (dir == LEFT && m_dir[dir]->get_pos().first < pos.first) ||
                       (dir == DOWN && m_dir[dir]->get_pos().second > pos.second) ||
                       (dir == UP && m_dir[dir]->get_pos().second < pos.second))))
    {
      if ((!cross || (!get_case() || (m_dir[dir] && m_dir[dir]->get_case()))) && !create)
        return (this);
      tmp.first = dir > 1 ? pos.first : m_pos.first;
      tmp.second = dir < 2 ? pos.second : m_pos.second;
      if (tmp.first == 0 || tmp.second == 0)
        lnk = new LnkCase(dir, m_map);
      else
        lnk = new LnkCase(NONE, m_map);
      lnk->set_pos(tmp);
      lnk->set_dir(INV_DIR(dir), this);
      lnk->set_dir(dir, m_dir[dir]);
      if (m_dir[dir])
        m_dir[dir]->set_dir(INV_DIR(dir), lnk);
      m_dir[dir] = lnk;
      return (lnk);
    }
  return (m_dir[dir]->get_next(dir, pos, create, cross));
}

void        LnkCase::set_pos(std::pair<int, int> pos)
{
  m_pos = pos;
}

void        LnkCase::set_dir(LnkDir dir,LnkCase *lnk)
{
  m_dir[dir] = lnk;
}

void        LnkCase::set_case(ClassCase *newCase)
{
  m_case = newCase;
}

bool        LnkCase::check_remove(bool forced)
{
  unsigned int  it;
  LnkCase       *tmp;

  if (((forced && !(get_pos().first == 0 && get_pos().second == 0)) ||
       (get_pos().first && get_pos().second)) && !m_case)
    {
      for (it = 0; it < 4; it++)
        {
          if ((tmp = get_dir((LnkDir)it)) && tmp->get_case())
            break;
        }
      if (it == 4)
        return (true);
    }
  return (false);
}

void        LnkCase::remove(bool forced)
{
  int     oth;
  int     it;

  it = 0;
  while (it < 4)
    {
      oth = it + 1;

      if (m_dir[it])
        m_dir[it]->set_dir((LnkDir)oth, m_dir[oth]);
      if (m_dir[oth])
        m_dir[oth]->set_dir((LnkDir)it, m_dir[it]);
      /*if (m_dir[it] && m_dir[it]->check_remove(forced))
            m_dir[it]->remove(forced);
        else
          m_dir[it] = NULL;
        if (m_dir[oth] && m_dir[oth]->check_remove(forced))
            m_dir[oth]->remove(forced );
        else
          m_dir[oth] = NULL;*/
      it += 2;
    }
  return ;
  for (it = 0; it < 4; it++)
    {
      if (m_dir[it])
        //delete m_dir[it];
        m_dir[it] = NULL;
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

ClassCase               *LnkCase::get_case()
{
  return (m_case);
}

LnkDir                  LnkCase::get_border()
{
  return (m_border);
}

ClassMap                *LnkCase::get_map()
{
  return (m_map);
}
