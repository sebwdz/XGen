
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Brain.hpp"
#include        "Cell/Module.hpp"

ModuleClass::ModuleClass(Object *parent) : Movable(parent)
{
    m_skel = new Skeleton();
    m_sig.insert(std::make_pair(KILL, (SIG_CATCH)(&ModuleClass::catch_kill)));
}

ModuleClass::~ModuleClass()
{
    delete m_skel;
}

void        ModuleClass::add_object(boost::shared_ptr<Object> obj)
{
    if (CAST(Decriptor*)(obj.get()) && !CAST(Brain*)(this))
        get_line()->shared_to_line(obj->get_line());
    obj->set_parent(this);
    m_obj.push_back(obj);
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
        mod = CAST(ModuleClass*)(it->get());
        if (mod)
        {
            mod->make_skeleton();
            m_skel->add_skeleton(mod->get_skeleton());
        }
    }
    m_skel->finish();
    m_pos = m_skel->get_pos();
    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (CAST(Decriptor*)(it->get()))
            it->get()->set_pos(m_pos);
    }
}

OBJECT_LIST::iterator       ModuleClass::get_begin()
{
    return (m_obj.begin());
}

OBJECT_LIST::iterator       ModuleClass::get_end()
{
    return (m_obj.end());
}

void        ModuleClass::exec()
{
    OBJECT_LIST::iterator    it;

    if (m_state == STATE_EXEC)
        return ;
    for (it = m_obj.begin(); it != m_obj.end(); it++)
        (*it)->exec();
    make_move_line();
}

void        ModuleClass::catch_signals()
{
    OBJECT_LIST::iterator                       obj;
    boost::unordered_map<unsigned int, SIG_CATCH>::iterator it;
    std::list<void*>::iterator                  arg;
    std::list<void*>                            sig;

    for (it = m_sig.begin(); it != m_sig.end(); it++)
    {
        sig = m_line.get_signal(it->first);
        for (arg = sig.begin(); arg != sig.end(); arg++)
            (this->*(it->second))(it->first, *arg);
    }
    for (obj = m_obj.begin(); obj != m_obj.end(); obj++)
    {
        if (CAST(SignalManager*)(obj->get()))
            CAST(SignalManager*)(obj->get())->catch_signals();
    }
    get_ready();
}

void        ModuleClass::move()
{
    OBJECT_LIST::iterator   it;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (CAST(Movable*)(it->get()) &&
                (CAST(Brain*)(this) || !CAST(Decriptor*)(it->get())))
        {
            CAST(Movable*)(it->get())->move();
        }
    }
    Movable::move();
}

void        ModuleClass::exec_move()
{
    OBJECT_LIST::iterator   it;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (CAST(Movable*)(it->get()) &&
                (CAST(Brain*)(this) || !CAST(Decriptor*)(it->get())))
        {
            CAST(Movable*)(it->get())->exec_move();
        }
    }
    Movable::exec_move();
}

void        ModuleClass::get_move_line(MovableLine *move, Object *from)
{
    OBJECT_LIST::iterator   it;

    if (from == m_parent)
      filter(move, true);
    if (move->m_inter.size())
    {
        for (it = m_obj.begin(); it != m_obj.end(); it++)
        {
            if (it->get() != from && CAST(Movable*)(it->get()) &&
            (CAST(Brain*)(this) || !CAST(Decriptor*)(it->get())))
            {
                CAST(Movable*)(it->get())->get_move_line(move, this);
            }
        }
    }
    filter(move, false);
    Movable::get_move_line(move, from);
}

void        ModuleClass::catch_simple(unsigned int code, void *sig)
{
}

void        ModuleClass::catch_duplic(unsigned int, void *sig)
{

}

void        ModuleClass::catch_kill(unsigned int code, void *sig)
{
    OBJECT_LIST::iterator   it;
    OBJECT_LIST::iterator   dest;
    ModuleClass             *modul;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
        if (sig == it->get())
            break;
    if (it == m_obj.end())
        return ;
    if (code == DESTROY && m_parent)
    {
        if ((modul = CAST(ModuleClass*)((Object*)(sig))))
        {
            for (dest = modul->get_begin(); dest != modul->get_end(); dest++)
                add_object(*dest);
        }
    }
    m_obj.erase(it);
}
