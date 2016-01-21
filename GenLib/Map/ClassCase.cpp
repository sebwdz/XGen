

#include        "Map/ClassMap.hpp"

ClassCase::ClassCase()
{
  m_parent = NULL;
}

ClassCase::~ClassCase()
{

}

void                            ClassCase::set_lnk(LnkCase *parent)
{
  m_parent = parent;
}

void                            ClassCase::set_size(int size)
{
  m_size = size;
}

void                            ClassCase::add_obj(Object* obj)
{
  obj->set_case(this);
  m_obj.push_back(obj);
}

void                            ClassCase::remove_obj(ObjectMap *obj)
{
  std::list<Object*>::iterator         it;
  std::list<Object*>::iterator         end = m_obj.end();

  for (it = m_obj.begin(); it != end; it++)
    {
      if (obj == *it)
        {
          m_obj.erase(it);
          return ;
        }
    }
}

std::list<Object*>       &ClassCase::get_obj()
{
  return (m_obj);
}

int                         ClassCase::get_size() const
{
  return (m_size);
}

LnkCase                   *ClassCase::get_lnk() const
{
  return (m_parent);
}

void                        ClassCase::interact_with(MovableLine *move)
{
  std::list<Object*>::iterator   it;
  std::list<Object*>::iterator   end = m_obj.end();

  for (it = m_obj.begin(); it != end; it++)
    {
      if ((*it)->get_type() & TYPE_MOVABLE && *it != move->get_parent())
        move->interact(CAST(Movable*)(*it), OTH);
    }
}

void                                ClassCase::cross_map(MovableLine *move, LnkCase *lnk)
{
  static std::vector<LnkCase*>    cases;
  unsigned int                    it;
  unsigned int                    nb;
  int                             dir;
  LnkCase*                        tmp;

  if (cases.size())
    cases[0] = lnk;
  else
    cases.push_back(lnk);
  nb = 1;
  for (it = 0; it < nb; it++)
    {
      if ((cases[it]->get_case()))
        cases[it]->get_case()->interact_with(move);
      dir = 0;
      while (dir < 4) {
          tmp = cases[it]->get_dir((LnkDir)dir);
          if (tmp && get_dist(tmp, move) &&
              std::find(cases.begin(), cases.begin() + nb, tmp) == cases.begin() + nb)
            {
              if (nb < cases.size())
                cases[nb] = tmp;
              else
                cases.push_back(tmp);
              nb++;
            }
          dir++;
        }
    }
}

bool                        ClassCase::get_dist(LnkCase *lnk, MovableLine *move) const
{
  float                   dst;
  float                   tmp;
  std::pair<float, float> vct;
  int                     tmpsize;
  std::pair<int, int>     range = move->get_range();

  tmpsize = m_size / 5;
  if (lnk->get_map())
    {
      vct.first = (lnk->get_pos().first * tmpsize) - move->get_parent()->get_pos().first;
      vct.second = (lnk->get_pos().second * tmpsize) - move->get_parent()->get_pos().second;
      dst = (vct.first * vct.first) + (vct.second * vct.second);
      tmp = range.second * range.second + (tmpsize * tmpsize);
      if (dst < tmp)
        return (true);
    }
  return (false);
}
