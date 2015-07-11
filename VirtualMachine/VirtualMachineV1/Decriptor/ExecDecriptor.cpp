
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
    bool    use = false;

    if (node->get_value() == USE)
        use = true;
    for (it = node->get_begin(); it != node->get_end(); it++)
        get_line()->get_chan(CAST(GeneticalNode*)((*it).get())->get_value())->set_use(use);
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
    unsigned int    val;
    unsigned int    tmp;

    if (node->get_begin() != node->get_end())
    {
        /*if ((tmp = get_line()->get_value(JMP_CHAN)) >= 5)
        {
            val = CAST(GeneticalNode*)(node->get_begin()->get())->get_value();
            val = get_line()->get_value(val);
            m_jmp = val;
            tmp -= 5;
            get_line()->set_value(JMP_CHAN, tmp);
        }*/
    }
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
    return (0);
}

void        Decriptor::set_chan(GeneticalNode *node)
{
    GeneticalNode   *cp;
    Chanel          *chan;
    OBJ_IT          it;

    chan = get_line()->get_chan(node->get_value());
    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        cp = CAST(GeneticalNode*)(it->get());
        if (cp->get_value() == RPLS)
            set_propriety(cp, chan, -1);
        else if (cp->get_value() == ATR)
            set_propriety(cp, chan, 1);
        else if (cp->get_value() == WGTH)
        {
            if (cp->get_begin() != cp->get_end())
            {
                cp = CAST(GeneticalNode*)(cp->get_begin()->get());
                chan->set_wgth(cp->get_value());
            }
        }
    }
}

chanPropriety       *Decriptor::get_propriety_chan(GeneticalNode *node, Chanel *chan, unsigned int ref)
{
    OBJ_IT          it;
    bool            id[2] = {false};
    int             cmp;
    GeneticalNode   *cp;

    cmp = 0;
    for (it = node->get_begin(); it != node->get_end() && cmp < 2; it++)
    {
        cp = CAST(GeneticalNode*)(it->get());
        if (cp->get_value() == TO || cp->get_value() == MV)
            id[cmp] = true;
        else
            id[cmp] = false;
        cmp++;
    }
    return (chan->get_propriety(ref, id[0], id[1]));
}

void        Decriptor::set_propriety(GeneticalNode *node, Chanel *chan, float val)
{
    OBJ_IT          it;
    OBJ_IT          it2;
    chanPropriety   *pr;
    GeneticalNode   *cp;
    GeneticalNode   *cppr;

    for (it = node->get_begin(); it != node->get_end(); it++)
    {
        cp = CAST(GeneticalNode*)(it->get());
        it2 = cp->get_begin();
        if (it2 == cp->get_end())
            continue ;
        cppr = CAST(GeneticalNode*)(it2->get());
        if (cppr->get_value() != 0)
            continue ;
        pr = get_propriety_chan(cppr, chan, cp->get_value());
        it2++;
        while (it2 != cp->get_end())
        {
            cppr = CAST(GeneticalNode*)(it2->get());
            if (cppr->get_begin() != cppr->get_end())
            {
                if (cppr->get_value() == DST)
                    pr->m_dist = CAST(GeneticalNode*)(cppr->get_begin()->get())->get_value();
                else if (cppr->get_value() == PW)
                    pr->m_pow = CAST(GeneticalNode*)(cppr->get_begin()->get())->get_value() * val;
            }
            it2++;
        }
    }
}
