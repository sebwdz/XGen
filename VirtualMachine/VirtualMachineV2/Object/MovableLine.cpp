
#include        "Decriptor/Decriptor.hpp"

MovableLine::MovableLine()
{

}

MovableLine::~MovableLine()
{

}

void            MovableLine::make()
{
    CHANPLIST::iterator         it;

    m_move.first = 0;
    m_move.second = 0;
    it = m_parent->get_line()->get_begin_prop();
    m_inter.clear();
    while (it != m_parent->get_line()->get_end_prop())
    {
        m_inter.insert(std::make_pair(it->first, it->second));
        it++;
    }
    while (m_stoped.size())
        m_stoped.pop();
    make_range();
}

void            MovableLine::make_range()
{
    float                               dst;
    float                               tmp;
    std::vector<float>::iterator        it2;
    CHANPLIST::iterator                 it;

    for (it = m_inter.begin(); it != m_inter.end(); it++)
    {
        dst = it->second->get_pow(DST);
        tmp = 10;
        while (tmp * 5 < dst)
            tmp *= 5;
        dst = tmp;
        for (it2 = m_range.begin(); it2 != m_range.end(); it2++)
        {
            if (*it2 == dst)
                break;
            else if (*it2 > dst)
            {
                m_range.insert(it2, dst);
                break;
            }
        }
        if (m_range.end() == it2)
            m_range.push_back(dst);
    }
}

void            MovableLine::filter(Object *obj, bool stop)
{
    CHANPLIST::iterator     it;
    CHANPLIST::iterator     rm;

    if (stop)
    {
        it = m_inter.begin();
        while (it != m_inter.end())
        {
            if (!obj->get_line()->get_value(it->second->get_act()[0], true) ||
                    !obj->get_line()->get_value(it->second->get_act()[1], true))
            {
                m_stoped.push(std::make_pair(it->second, obj));
                rm = it++;
                m_inter.erase(rm);
            }
            else
                it++;
        }
    }
    else
    {
        while (m_stoped.size() && m_stoped.top().second == obj)
        {
            m_inter.insert(std::make_pair(m_stoped.top().first->get_ref(), m_stoped.top().first));
            m_stoped.pop();
        }
    }
}

void            MovableLine::change_chan(unsigned int ref, sMovableChan *move)
{
    boost::unordered_map<Object*, float>::iterator  it;
    LineDecript                                     *line;
    float                                           tmp;
    float                                           all;
    float                                           use;

    it = move->obj.begin();
    all = 0;
    use = move->total < move->have ? move->have : move->total;
    tmp = 0;
    while (it != move->obj.end())
    {
        if (it->second > 0)
        {
            line = it->first->get_line();
            tmp += (it->second / use) * move->have;
            all += tmp;
            tmp = tmp + line->get_chan(ref)->get_value();
            line->get_chan(ref)->set_value(tmp);
            it->second = 0;
        }
        it++;
    }
    m_parent->get_line()->get_chan(ref)->set_value(m_parent->get_line()->get_chan(ref)->get_value() - all);
    move->life = 0;
    move->total = 0;
    move->obj.clear();
}

void            MovableLine::exec()
{
    std::pair<float, float>     pos;
    CHAN_MOVELIST::iterator     it;
    CHAN_MOVELIST::iterator     rm;

    pos = m_parent->get_pos();
    pos.first += m_move.first;
    pos.second += m_move.second;
    m_parent->set_pos(pos);
    it = m_change.begin();
    while (it != m_change.end())
    {
        if (it->second->total != 0) {
            change_chan(it->first, it->second);
        }
        else
            it->second->life++;
        if (it->second->life > 20) {
            rm = it++;
            delete rm->second;
            m_change.erase(rm);
        }
        else
            it++;
    }
}

void            MovableLine::interact_with(class Movable *obj, ChanPropriety *prop)
{
    std::pair<float, float>         vct;
    std::pair<float, unsigned int>  chan;
    unsigned int                    tmp[2];
    float                           lentmp;

    vct = m_vct;
    if (prop->get_type(ATTACH))
    {
        check_attach(obj, prop);
        return ;
    }
    if (prop->get_type(OTH))
    {
        vct.first *= -1;
        vct.second *= -1;
    }
    if ((tmp[0] = m_parent->get_line()->get_value(prop->get_act()[0])) &&
            (tmp[1] = obj->get_line()->get_value(prop->get_act()[1])))
    {
        chan.first = tmp[0] + tmp[1];
        chan.first *= prop->get_pow(PW) / 100;
        chan.first *= prop->get_type(RPLS) ? -1 : 1;
        lentmp = (prop->get_pow(DST) - m_len) / prop->get_pow(DST);
        chan.first *= lentmp * 3.14 / 4;
        chan.second = prop->get_type(OTH) ? prop->get_act()[1] : prop->get_act()[0];
        if (prop->get_type(OTH))
            obj->get_move_line()->apply(m_parent, prop, vct, chan);
         else
            apply(obj, prop, vct, chan);
    }
}

void            MovableLine::interact(Movable *obj)
{
    CHANPLIST::iterator             it;

    m_vct.first = obj->get_pos().first - m_parent->get_pos().first + (((rand() % 100) - 50) / 200.0);
    m_vct.second = obj->get_pos().second - m_parent->get_pos().second + (((rand() % 100) - 50) / 200.0);
    m_len = m_vct.first * m_vct.first + m_vct.second * m_vct.second;
    if (m_len > 0)
    {
        m_len = sqrt(m_len);
        m_vct.first /= m_len;
        m_vct.second /= m_len;
        if (m_range.size() && m_len < m_range.back())
        {
            for (it = m_inter.begin(); it != m_inter.end(); it++)
            {
                if (it->second->get_pow(DST) > m_len)
                {
                    interact_with(obj, it->second);
                }
            }
        }
    }
}

void            MovableLine::apply(Movable *from, ChanPropriety *prop, std::pair<float, float> &vct, std::pair<float, unsigned int> &chan)
{
    sMovableChan            *move;
    float                   tmp;

    if (prop->get_type(MV))
    {
        m_move.first += vct.first * chan.first;
        m_move.second += vct.second * chan.first;
    }
    else
    {
        if (m_change.find(chan.second) == m_change.end())
        {
            move = new sMovableChan;
            move->life = 0;
            move->total = 0;
            move->have =  m_parent->get_line()->get_chan(chan.second)->get_value();
            m_change.insert(std::make_pair(chan.second, move));
        }
        if (m_change[chan.second]->obj.find(from) == m_change[chan.second]->obj.end())
            m_change[chan.second]->obj.insert(std::make_pair(from, 0));
        tmp = 0;
        if (m_change[chan.second]->obj[from] < 0 && chan.first > 0 && chan.first > m_change[chan.second]->obj[from] * -1)
        {
            tmp = chan.first + m_change[chan.second]->obj[from];
        }
        else if (m_change[chan.second]->obj[from] > 0 && chan.first < 0)
        {
            if (m_change[chan.second]->obj[from] > chan.first - 1)
                tmp = chan.first + m_change[chan.second]->obj[from];
            else
                tmp = chan.first;
        }
        else if (chan.first > 0)
            tmp = chan.first;
        m_change[chan.second]->obj[from] += chan.first;
        m_change[chan.second]->total += tmp;
    }
}

bool              MovableLine::check_attach(Object *obj, ChanPropriety *prop)
{
    if (obj->get_line()->get_value(prop->get_act()[0]) > 0 &&
            obj->get_line()->get_value(prop->get_act()[1]) < 1)
    {
        if (!CAST(Decriptor*)(obj) && CAST(Decriptor*)(m_parent))
        {
            m_parent->add_signal(ATTACH, static_cast<void*>(obj));
            return (true);
        }
    }
    return (false);
}


void            MovableLine::set_parent(Movable *parent)
{
    m_parent = parent;
}

Movable*        MovableLine::get_parent()
{
    return (m_parent);
}

CHANPLIST       &MovableLine::get_inter()
{
    return (m_inter);
}
