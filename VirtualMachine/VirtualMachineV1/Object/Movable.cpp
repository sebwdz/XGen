
#include        <cmath>
#include        "Object/Movable.hpp"

Movable::Movable(Object *parent) : SignalManager(parent)
{
    m_moveLine.m_parent = this;
}

Movable::~Movable()
{

}

void            Movable::move()
{
    boost::unordered_map<unsigned int, MOVABLE_CHAN>::iterator it;
    boost::unordered_map<Object*, float>::iterator lst;
    float                                           value;
    float                                           all;
    float                                           tmp;
    float                                           weight;

    m_state = STATE_MOVE;
    if (m_parent && CAST(Movable*)(m_parent))
        CAST(Movable*)(m_parent)->get_move_line(&m_moveLine, this);
    weight = 1;
    if (m_moveLine.m_move.second > 0)
    {
        m_pos.first += m_moveLine.m_move.first.first / weight;
        m_pos.second += m_moveLine.m_move.first.second / weight;
    }
    for (it = m_moveLine.m_change.begin(); it != m_moveLine.m_change.end(); it++)
    {
        all = 0;
        value = it->second.second;
        if (m_moveLine.m_parent->get_line()->get_chan(it->first)->get_use() && value)
        {
            if (m_moveLine.m_parent->get_line()->get_chan(it->first)->get_value() > 0)
            {
                for (lst = it->second.first.begin(); lst != it->second.first.end(); lst++)
                {
                    if (it->second.second < get_line()->get_chan(it->first)->get_value())
                        value = get_line()->get_chan(it->first)->get_value();
                    tmp = (lst->second / value) * get_line()->get_chan(it->first)->get_value();
                    if (tmp)
                    {
                        lst->first->get_line()->get_chan(it->first)->
                            set_value(tmp + lst->first->get_line()->get_chan(it->first)->get_value());
                        all += tmp;
                    }
                }
            }
            all = get_line()->get_chan(it->first)->get_value() - all;
            get_line()->get_chan(it->first)->set_value(all);
        }
    }
}

void            Movable::make_move_line()
{
    m_state = STATE_EXEC;
    m_moveLine.m_change.clear();
    m_moveLine.m_move.first.first = 0;
    m_moveLine.m_move.first.second = 0;
    m_moveLine.m_move.second = 0;
}

void            Movable::filter(MovableLine *line, bool stop)
{
    USE_LIST::iterator                         chan;
    std::list<std::pair<unsigned int, Object*> >::iterator    it;
    std::list<std::pair<unsigned int, Object*> >::iterator    rm;

    if (!stop)
    {
        for (it = line->m_stoped.begin(); it != line->m_stoped.end(); it++)
        {
             if (it->second == this)
             {
                 rm = it--;
                 line->m_stoped.erase(rm);
             }
        }
    }
    else
    {
        for (chan = m_moveLine.m_parent->get_line()->get_begin();
                chan != m_moveLine.m_parent->get_line()->get_end(); chan++)
        {
            if (!m_moveLine.m_parent->get_line()->get_chan(chan->first)->get_use())
                line->m_stoped.push_back(std::make_pair(chan->first, this));
        }
    }
}

void              Movable::apply(float pow, chanPropriety* prop, Object *from, unsigned int chan)
{
    if (prop->m_type)
    {
        m_moveLine.m_move.first.first += pow * m_moveLine.m_vct.first;
        m_moveLine.m_move.first.second += pow * m_moveLine.m_vct.second;
        m_moveLine.m_move.second += 1;
    }
    else
    {
        if (m_moveLine.m_change.find(prop->m_ref) == m_moveLine.m_change.end())
            m_moveLine.m_change.insert(std::make_pair(chan, std::make_pair(boost::unordered_map<Object*, float>(), 0)));
        if (m_moveLine.m_change[prop->m_ref].first.find(from) == m_moveLine.m_change[prop->m_ref].first.end())
            m_moveLine.m_change[prop->m_ref].first.insert(std::make_pair(from, 0));
        m_moveLine.m_change[prop->m_ref].first[from] += pow;
        m_moveLine.m_change[prop->m_ref].second += pow;
    }
}

void              Movable::interact_with(MovableLine *from, MovableLine *to, Chanel *chan, MovableLine *stp)
{
    float               pow;
    CHAN_P::iterator    it;
    Chanel              *tmp;

    if (!chan->get_value())
        return ;
    for (it = chan->get_begin(); it != chan->get_end(); it++)
    {
        if (stp->m_parent->is_stop((*it)->m_ref))
            continue;
        if ((tmp = to->m_parent->get_line()->get_chan((*it)->m_ref)))
        {
            if (!tmp->get_value())
                continue;
            if ((*it)->m_dist < from->m_len && (*it)->m_dist)
                continue;
            pow = tmp->get_value() + chan->get_value();
            pow *= (*it)->m_pow / 100;
            if ((*it)->m_dist)
                pow *= ((*it)->m_dist - from->m_len) / ((*it)->m_dist);
            if ((*it)->m_dir)
                from->m_parent->apply(pow, *it, to->m_parent, chan->get_ref());
            else
                to->m_parent->apply(pow, *it, from->m_parent, chan->get_ref());
        }
    }
}

void            Movable::get_interact(MovableLine *move)
{
    USE_LIST::iterator chan;

    move->m_vct.first = m_pos.first - move->m_parent->get_pos().first;
    move->m_vct.second = m_pos.second - move->m_parent->get_pos().second;
    move->m_vct.first += ((rand() % 100) - 50) / 200.0;
    move->m_vct.second += ((rand() % 100) - 50) / 200.0;
    move->m_len = move->m_vct.first * move->m_vct.first + move->m_vct.second * move->m_vct.second;
    move->m_len = sqrt(move->m_len);
    if (move->m_len)
    {
        move->m_vct.first /= move->m_len;
        move->m_vct.second /= move->m_len;
        m_moveLine.m_vct.first = move->m_vct.first * -1;
        m_moveLine.m_vct.second = move->m_vct.second * -1;
        m_moveLine.m_len = move->m_len;
        for (chan = move->m_parent->get_line()->get_begin();
                chan != move->m_parent->get_line()->get_end(); chan++)
        {
            if (!move->m_parent->is_stop(chan->first))
                interact_with(move, &m_moveLine, chan->second, move);
        }
        for (chan = get_line()->get_begin(); chan != get_line()->get_end(); chan++)
        {
            if (!move->m_parent->is_stop(chan->first))
                interact_with(&m_moveLine, move, chan->second, move);
        }
    }
}

void            Movable::get_move_line(MovableLine *move, Object *from)
{
    if (m_state == STATE_EXEC)
    {
        filter(move, true);
        get_interact(move);
        filter(move, false);
    }
    if (m_parent && m_parent != from && CAST(Movable*)(m_parent))
    {
        filter(move, true);
        CAST(Movable*)(m_parent)->get_move_line(move, this);
        filter(move, false);
    }
}

bool            Movable::is_stop(unsigned int chan)
{
    std::list<std::pair<unsigned int, Object*> >::iterator it;

    for (it = m_moveLine.m_stoped.begin();
         it != m_moveLine.m_stoped.end(); it++)
    {
        if (chan == it->first)
            return (true);
    }
    return (false);
}
