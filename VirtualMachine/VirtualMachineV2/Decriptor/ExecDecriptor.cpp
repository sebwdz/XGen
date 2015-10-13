
#include        "Cell/Brain.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/DecriptorManager.hpp"

void        Decriptor::exec()
{
    Monitor::get_instance()->begin_time(MN_INSTR);
    turn(m_node.get());
    Monitor::get_instance()->end_time(MN_INSTR);
    if (m_parent && CAST(Brain*)(m_parent))
    {
        m_state = STATE_EXEC;
        make_move_line();
    }
}

void        Decriptor::turn(GeneticalNode *node)
{
    int             (Decriptor::*fct)(GeneticalNode*);

    if (node->get_type() == INSTRU)
    {
        if (!node->get_function())
        {
            fct = DecriptorManager::get_instance()->get_function(node);
            node->set_function(fct);
        }
        else
            fct = node->get_function();
    }
    else
        fct = &Decriptor::nothing;
    Monitor::get_instance()->add_val(MN_INSTR);
    (this->*(fct))(node);
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
    unsigned int    it;
    Chanel          *tmp;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();

    it = 0;
    value2 = 0;
    for (it = 0; it + 1 < vct.size(); it++)
    {
        tmp = get_chan(CAST(GeneticalNode*)(vct[it++].get()));
        value1 = tmp->get_value();
        value2 = get_value(CAST(GeneticalNode*)(vct[it].get()));
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
    return (0);
}

int         Decriptor::comparator(GeneticalNode *node, GeneticalNode *content)
{
    unsigned int                    it;
    float                           value1;
    float                           value2;
    std::vector<SMART(ObjClass)>    &vct = content->get_son();

    value2 = 0;
    value1 = 0;
    it = 0;
    if (node->get_type() == INSTRU && vct.size() > 0 &&
            (node->get_value() == OR || node->get_value() == AND ||
                                       node->get_value() == XOR))
    {
        for (it = 0; it < vct.size(); it++)
        {
            value1 = comp_funcion(CAST(GeneticalNode*)(vct[it].get()));
            if (value2 && value1 && node->get_value() == XOR)
                return (0);
            if (node->get_value() == AND && !value1)
                return (0);
            if (!value2 && value1)
                value2 = value1;
        }
        if (!value2 && !value1 && (node->get_value() == OR || node->get_value() == XOR))
            return (0);
    }
    else if (node->get_value() == NO && vct.size() > 0)
        return (comp_funcion(CAST(GeneticalNode*)(vct[it].get())) ? 0 : 1);
    else if (vct.size() > 1)
    {
        value1 = get_value(CAST(GeneticalNode*)(vct[it++].get()));
        value2 = get_value(CAST(GeneticalNode*)(vct[it].get()));
        if (node->get_value() == SUP && value1 <= value2)
            return (0);
        else if (node->get_value() == INF && value1 >= value2)
            return (0);
        else if (node->get_value() == EGAL && value1 != value2)
            return (0);
    }
    else
        return (0);
    return (1);
}

int        Decriptor::comp_funcion(GeneticalNode *node)
{
    unsigned int    it;
    std::vector<SMART(ObjClass)>    &vct = node->get_son();
    GeneticalNode                   *content;

    it = 0;
    if (vct.size() > 0)
    {
        content = CAST(GeneticalNode*)(vct[0].get());
        if (comparator(node, content))
        {
            for (it = 1; it < vct.size(); it++)
                turn(CAST(GeneticalNode*)(vct[it].get()));
            return (1);
        }
    }
    return (0);
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
            get_chan(CAST(GeneticalNode*)(vct[it].get()))->set_use(use);
        else
            get_chan(CAST(GeneticalNode*)(vct[it].get()))->set_shared(use);
    }
    return (0);
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
    return (0);
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
        Monitor::get_instance()->add_val(MN_INSTR);
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
        Monitor::get_instance()->add_val(MN_INSTR);
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
        Monitor::get_instance()->add_val(MN_INSTR);
        cp = CAST(GeneticalNode*)(vct[it].get());
        if (node->get_value() == TYPE)
            prop->set_type(cp->get_value());
        else if (node->get_value() == DST || node->get_value() == PW) {
            prop->set_pow(node->get_value(), get_value(cp));
        }
        else if (node->get_value() == ACT)
        {
            if (it == 0)
                prop->set_act(TO, cp->get_value());
            else
                prop->set_act(OTH, cp->get_value());
        }
    }
}
