
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Brain.hpp"
#include        "Cell/Module.hpp"

ModuleClass::ModuleClass(Object *parent) : Movable(parent)
{
    m_skel = new Skeleton();
    m_map = new MapController();
    m_sig.insert(std::make_pair(KILL, (SIG_CATCH)(&ModuleClass::catch_kill)));
    m_sig.insert(std::make_pair(TAKEOUT, (SIG_CATCH)(&ModuleClass::catch_takeout)));
    m_sig.insert(std::make_pair(LINK, (SIG_CATCH)(&ModuleClass::catch_link)));
    m_type ^= TYPE_MODULE;
}

ModuleClass::~ModuleClass()
{
  unsigned int it;

  for (it = 0; it < m_decriptor.size(); it++)
    delete m_decriptor[it];
  for (it = 0; it < m_obj.size(); it++)
    {
      m_map->remove_object(m_obj[it]);
      delete m_obj[it];
    }
  for (it = 0; it < m_links.size(); it++)
    {
      m_links[it]->link(this, false);
    }
  delete m_skel;
  delete m_map;
}

void        ModuleClass::add_object(Object *obj)
{
    obj->set_parent(this);
    if (obj->get_type() & TYPE_DECRIPTOR && !(m_type & TYPE_BRAIN))
      {
        get_line()->shared_to_line(obj->get_line());
        m_decriptor.push_back(obj);
      }
    else
    {
        m_map->add_obj(obj);
        m_obj.push_back(obj);
    }
}

Skeleton                    *ModuleClass::get_skeleton()
{
    return (m_skel);
}

void                        ModuleClass::make_skeleton()
{
    OBJECT_LIST::iterator   it;
    ModuleClass             *mod;

    m_skel->clear();
    m_skel->set_pos(m_pos);
    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        mod = CAST(ModuleClass*)(*it);
        if (mod)
        {
            mod->make_skeleton();
            m_skel->add_skeleton(mod->get_skeleton());
        }
    }
    m_skel->finish();
}

OBJECT_LIST::iterator       ModuleClass::get_begin()
{
    return (m_obj.begin());
}

OBJECT_LIST::iterator       ModuleClass::get_end()
{
    return (m_obj.end());
}

ClassMap    *ModuleClass::get_map()
{
    return (m_map->get_map());
}

void        ModuleClass::exec()
{
    unsigned int            it;

    catch_signals();
    for (it = 0; it < m_decriptor.size(); it++)
        m_decriptor[it]->exec();
    for (it = 0; it != m_obj.size(); it++)
    {
        m_obj[it]->exec();
        if (m_obj[it]->get_parent() != this)
        {
            m_map->get_map()->remove_object(m_obj[it]);
            delete m_obj[it];
            m_obj.erase(m_obj.begin() + it--);
        }
    }
    make_move_line();
}

void        ModuleClass::move()
{
    unsigned int    it;

    for (it = 0; it != m_obj.size(); it++)
    {
        if (m_obj[it]->get_type() & TYPE_MOVABLE)
            CAST(Movable*)(m_obj[it])->move();
    }
    for (it = 0; it < m_links.size(); it++)
      {
        if (m_links[it]->get_parent() != m_parent)
          m_moveLine.interact(m_links[it]);
      }
    Movable::move();
}

void        ModuleClass::exec_move()
{
    unsigned int    it;

    for (it = 0; it != m_obj.size(); it++)
    {
        if (m_obj[it]->get_type() & TYPE_MOVABLE)
        {
            CAST(Movable*)(m_obj[it])->exec_move();
            m_map->move_object(m_obj[it]);
        }
    }
    Movable::exec_move();
    cal_pos();
}

void        ModuleClass::catch_duplic(unsigned int code, void *sig)
{
    (void)code;
    (void)sig;
}

void        ModuleClass::catch_kill(unsigned int code, void *sig)
{
    OBJECT_LIST::iterator   it;
    OBJECT_LIST::iterator   dest;
    ModuleClass             *modul;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (sig == *it)
            break;
    }
    if (it == m_obj.end())
        return ;
    if (code == DESTROY && m_parent)
    {
        if (((Object*)(sig))->get_type() & TYPE_MODULE)
        {
            modul = CAST(ModuleClass*)(sig);
            for (dest = modul->get_begin(); dest != modul->get_end(); dest++)
                add_object(*dest);
        }
    }
    m_map->remove_object(*it);
    delete *it;
    m_obj.erase(it);
}

void        ModuleClass::catch_takeout(unsigned int code, void *sig)
{
    ModuleClass             *to;
    OBJECT_LIST::iterator   it;

    if (m_parent && m_parent->get_type() & TYPE_MODULE)
    {
        to = CAST(ModuleClass*)(m_parent);
        for (it = m_obj.begin(); it != m_obj.end(); it++)
        {
            if (sig == *it)
                break;
        }
        if (it == m_obj.end())
            return ;
        m_map->remove_object(*it);
        to->add_object(*it);
        m_obj.erase(it);
    }
}

void          ModuleClass::link(ModuleClass *obj, bool link)
{
  if (link)
    {
      m_links.push_back(obj);
      return ;
    }
  for (unsigned int it = 0; it < m_links.size(); it++)
    {
      if (m_links[it] == obj)
        {
          m_links.erase(m_links.begin() + it);
          return ;
        }
    }
}

void          ModuleClass::catch_link(unsigned int code, void *sig)
{
  ModuleClass *oth;

  oth = static_cast<ModuleClass*>(sig);
  if (oth->get_begin() != oth->get_end() || m_obj.size())
    return ;
  for (unsigned int it = 0; it < m_links.size(); it++)
    {
      if (m_links[it] == oth)
        return ;
    }
  oth->link(this, true);
  link(oth, true);
}

void                    ModuleClass::cal_pos()
{
    unsigned int            it;
    std::pair<float, float> pos;
    int                     nb;

    pos.first = 0;
    pos.second = 0;
    nb = 0;
    for (it = 0; it < m_obj.size(); it++)
    {
        if (m_obj[it]->get_type() & TYPE_MOVABLE) {
            nb++;
            pos.first += m_obj[it]->get_pos().first;
            pos.second += m_obj[it]->get_pos().second;
        }
    }
    if (nb)
    {
        pos.first /= nb;
        pos.second /= nb;
        m_pos = pos;
    }
}
