
#include        "Cell/Brain.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/DecriptorManager.hpp"

void        Decriptor::exec()
{
    if ((m_parent && CAST(Brain*)(m_parent)) && m_state == STATE_EXEC)
        return ;
    turn(m_node);
    if (!(m_parent && CAST(Brain*)(m_parent)))
        make_move_line();
}

void        Decriptor::turn(GeneticalNode *node)
{
    int (Decriptor::*ptr)(GeneticalNode*);

    if (!m_jmp)
        ptr = DecriptorManager::get_instance()->get_function(node);
    else
    {
        m_jmp--;
        ptr = &Decriptor::nothing;
    }
    (this->*ptr)(node);
}

int             Decriptor::nothing(GeneticalNode *node)
{
    OBJ_IT      it;

    for (it = node->get_begin(); it != node->get_end(); it++)
        turn(CAST(GeneticalNode*)((*it).get()));
    return (0);
}

int        Decriptor::set_function(GeneticalNode *node)
{
    unsigned int    value1;
    unsigned int    value2;
    unsigned int    reg;
    OBJ_IT          it;

    value2 = 0;
    if ((it = node->get_begin()) != node->get_end())
    {
        reg = CAST(GeneticalNode*)((*(it++)).get())->get_value();
        if (it != node->get_end())
            value2 = CAST(GeneticalNode*)((*it).get())->get_value();
        value1 = get_line()->get_chan(reg)->get_value();
        if (value2 >= CHANNEL_RANGE)
            value2 = get_line()->get_chan(value2)->get_value();
        if (node->get_value() == SET)
            value1 = value2;
        else if (node->get_value() == ADD)
            value1 += value2;
        else if (value1 > value2)
            value1 -= value2;
        else
            value1 = 0;
        get_line()->get_chan(reg)->set_value(value1);
        value1 = get_line()->get_chan(reg)->get_value();
    }
    return (nothing(node));
}

int        Decriptor::comp_funcion(GeneticalNode *node)
{
    unsigned int    value1;
    unsigned int    value2;
    OBJ_IT          it;

    value2 = 0;
    if ((it = node->get_begin()) != node->get_end())
    {
        value1 = CAST(GeneticalNode*)((*(it++)).get())->get_value();
        if (it != node->get_end())
            value2 = CAST(GeneticalNode*)((*it).get())->get_value();
        value1 = get_line()->get_chan(value1)->get_value();
        if (value2 >= CHANNEL_RANGE)
            value2 = get_line()->get_chan(value2)->get_value();
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
    OBJ_IT  it;

    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        get_line()->add_signal(node->get_value(), it->get());
    }
    return (0);
}

int         Decriptor::use_function(GeneticalNode *node)
{
    OBJ_IT  it;
    bool    use;
    bool    mode;

    use = false;
    if (node->get_value() == USE || node->get_value() == SHARED)
        use = true;
    mode = true;
   if (node->get_value() == USE || node->get_value() == UNUSE)
        mode = false;
    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        if (!mode)
            get_line()->get_chan(CAST(GeneticalNode*)((*it).get())->get_value())->set_use(use);
        else
            get_line()->get_chan(CAST(GeneticalNode*)((*it).get())->get_value())->set_shared(use);
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

    /*if (node->get_begin() != node->get_end())
    {
        if ((tmp = get_line()->get_value(JMP_CHAN)) >= 5)
        {
            val = CAST(GeneticalNode*)(node->get_begin()->get())->get_value();
            val = get_line()->get_value(val);
            m_jmp = val;
            tmp -= 5;
            get_line()->set_value(JMP_CHAN, tmp);
        }
    }*/
    return (nothing(node));
}

int             Decriptor::set_var_function(GeneticalNode *node)
{
    OBJ_IT          it;
    GeneticalNode   *cur;

    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        cur = CAST(GeneticalNode*)(it->get());
        set_chan(cur);
    }
    return (nothing(node));
}

void        Decriptor::set_chan(GeneticalNode *node)
{
    GeneticalNode   *cp;
    ChanPropriety   *prop;
    OBJ_IT          it;

    prop = get_line()->get_prop(node->get_value());
    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        cp = CAST(GeneticalNode*)(it->get());
        set_propriety(cp, prop);
    }
}

void        Decriptor::set_propriety(GeneticalNode *node, ChanPropriety *prop)
{
    OBJ_IT          it;
    GeneticalNode   *cp;

    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        cp = CAST(GeneticalNode*)(it->get());
        if (node->get_value() == TYPE)
            prop->set_type(cp->get_value());
        else if (node->get_value() == DST || node->get_value() == PW)
            prop->set_pow(node->get_value(), cp->get_value());
        else if (node->get_value() == ACT)
        {
            if (it == node->get_begin())
                prop->set_act(TO, cp->get_value());
            else
                prop->set_act(OTH, cp->get_value());
        }
    }
}
