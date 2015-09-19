
#include        "Cell/Brain.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/DecriptorManager.hpp"

void        Decriptor::exec()
{
    Monitor::get_instance()->begin_instru();
    turn(m_node);
    Monitor::get_instance()->end_instru();
    if (m_parent && CAST(Brain*)(m_parent))
    {
        m_state = STATE_EXEC;
        make_move_line();
    }
}

void        Decriptor::turn(GeneticalNode *node)
{
    decriptFunction ptr;

    if (node->get_type() == INSTRU)
    {
        if (!node->get_function())
        {
            ptr.fct = DecriptorManager::get_instance()->get_function(node);
            node->set_function(ptr.fct);
        }
        else {
            ptr.fct = node->get_function();
        }
    }
    else
        ptr.fct = &Decriptor::nothing;
    Monitor::get_instance()->add_instru();
    (this->*(ptr.fct))(node);
}

int             Decriptor::nothing(GeneticalNode *node)
{
    int         it;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    for (it = 0; it < (int)vct.size(); it++)
        turn(CAST(GeneticalNode*)(vct[it].get()));
    return (0);
}

int        Decriptor::set_function(GeneticalNode *node)
{
    unsigned int    value1;
    unsigned int    value2;
    int             it;
    Chanel          *tmp;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    it = 0;
    value2 = 0;
    if (vct.size() > 1)
    {
        value1 = CAST(GeneticalNode*)(vct[it++].get())->get_value();
        value2 = CAST(GeneticalNode*)(vct[it].get())->get_value();
        tmp = get_line()->get_chan(value1);
        value1 = tmp->get_value();
        if (CAST(GeneticalNode*)(vct[it].get())->get_type() == GLOBAL_CHAN)
            value2 = get_line()->get_value(value2);
        if (node->get_value() == SET)
            value1 = value2;
        else if (node->get_value() == ADD)
            value1 += value2;
        else if (value1 > value2)
            value1 -= value2;
        else
            value1 = 0;
        tmp->set_value(value1);
    }
    return (nothing(node));
}

int        Decriptor::comp_funcion(GeneticalNode *node)
{
    unsigned int    value1;
    unsigned int    value2;
    int             it;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    value2 = 0;
    it = 0;
    if (vct.size() > 2)
    {
        value1 = CAST(GeneticalNode*)(vct[it++].get())->get_value();
        value2 = CAST(GeneticalNode*)(vct[it].get())->get_value();
        value1 = get_line()->get_value(value1);
        if (CAST(GeneticalNode*)(vct[it].get())->get_type() == GLOBAL_CHAN)
            value2 = get_line()->get_value(value2);
        if (node->get_value() == SUP && value1 <= value2)
            return (1);
        else if (node->get_value() == INF && value1 >= value2)
            return (1);
        else if (node->get_value() == EGAL && value1 != value2)
            return (1);
    }
    return (nothing(node));
}

int         Decriptor::creat_function(GeneticalNode *node)
{
    get_line()->add_signal(node->get_value(), node);
    return (0);
}

int         Decriptor::use_function(GeneticalNode *node)
{
    int     it;
    bool    use;
    bool    mode;
    std::vector<SMART(ObjClass)>        &vct = node->get_son();

    use = false;
    if (node->get_value() == USE || node->get_value() == SHARED)
        use = true;
    mode = true;
   if (node->get_value() == USE || node->get_value() == UNUSE)
        mode = false;
    for (it = 0; it < (int)vct.size(); it++)
    {
        if (!mode)
            get_line()->get_chan(CAST(GeneticalNode*)(vct[it].get())->get_value())->set_use(use);
        else
            get_line()->get_chan(CAST(GeneticalNode*)(vct[it].get())->get_value())->set_shared(use);
    }
    return (nothing(node));
}

int         Decriptor::decript_function(GeneticalNode *node)
{
    if (node->get_value() == KILL && m_parent)
    {
        if (!CAST(Brain*)(m_parent) && m_parent->get_parent())
            m_parent->get_parent()->get_line()->add_signal(node->get_value(), m_parent);
        else
            m_parent->get_line()->add_signal(node->get_value(), this);
    }
    else
        get_line()->add_signal(node->get_value(), this);
    return (nothing(node));
}

int     Decriptor::jmp_function(GeneticalNode *node)
{
    return (nothing(node));
}

int             Decriptor::set_var_function(GeneticalNode *node)
{
    int              it;
    GeneticalNode   *cur;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    for (it = 0; it < (int)vct.size(); it++)
    {
        Monitor::get_instance()->add_instru();
        cur = CAST(GeneticalNode*)(vct[it].get());
        set_chan(cur);
    }
    return (0);
}

void        Decriptor::set_chan(GeneticalNode *node)
{
    GeneticalNode   *cp;
    ChanPropriety   *prop;
    int             it;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    prop = get_line()->get_prop(node->get_value());
    for (it = 0; it < (int)vct.size(); it++)
    {
        Monitor::get_instance()->add_instru();
        cp = CAST(GeneticalNode*)(vct[it].get());
        set_propriety(cp, prop);
    }
}

void        Decriptor::set_propriety(GeneticalNode *node, ChanPropriety *prop)
{
    int          it;
    GeneticalNode   *cp;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    for (it = 0; it < (int)vct.size(); it++)
    {
        Monitor::get_instance()->add_instru();
        cp = CAST(GeneticalNode*)(vct[it].get());
        if (node->get_value() == TYPE)
            prop->set_type(cp->get_value());
        else if (node->get_value() == DST || node->get_value() == PW) {
            // check value type
            prop->set_pow(node->get_value(), cp->get_value());
        }
        else if (node->get_value() == ACT)
        {
            // check for reference
            if (it == 0)
                prop->set_act(TO, cp->get_value());
            else
                prop->set_act(OTH, cp->get_value());
        }
    }
}
