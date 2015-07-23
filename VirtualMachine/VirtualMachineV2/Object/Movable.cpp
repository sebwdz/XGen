
#include        <cmath>
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"

Movable::Movable(Object *parent) : SignalManager(parent)
{
    m_moveLine.m_parent = this;
}

Movable::~Movable()
{

}

void            Movable::move()
{
    m_state = STATE_MOVE;
    if (m_parent && CAST(Movable*)(m_parent) && m_moveLine.m_inter.size())
        get_move_line(&m_moveLine, this);
}

void            Movable::exec_move()
{
    CHAN_MOVELIST::iterator                                 chan;
    boost::unordered_map<Object*, float>::iterator           it;
    float                           all;
    float                           tmp;
    float                           ref;

    m_pos.first += m_moveLine.m_move.first;
    m_pos.second += m_moveLine.m_move.second;
    for (chan = m_moveLine.m_change.begin(); chan != m_moveLine.m_change.end(); chan++)
    {
        all = 0;
        ref = chan->second.first.second > chan->second.second ? chan->second.first.second : chan->second.second;
        for (it = chan->second.first.first.begin(); it != chan->second.first.first.end(); it++)
        {
            if (it->second > 0)
            {
                tmp = (it->second / ref) * chan->second.second;
                all += tmp;
                tmp += it->first->get_line()->get_chan(chan->first)->get_value();
                it->first->get_line()->get_chan(chan->first)->set_value(tmp);
            }
        }
        tmp = get_line()->get_chan(chan->first)->get_value() - all;
        get_line()->get_chan(chan->first)->set_value(tmp);
    }
}

void            Movable::make_move_line()
{
    m_state = STATE_EXEC;
    m_moveLine.m_change.clear();
    m_moveLine.m_move.first = 0;
    m_moveLine.m_move.second = 0;
    m_moveLine.m_move.second = 0;
    m_moveLine.m_inter.clear();
    m_moveLine.m_inter.insert(get_line()->get_begin_prop(), get_line()->get_end_prop());
}

void            Movable::filter(MovableLine *line, bool stop)
{
    CHANPLIST::iterator                                        it;

    if (!stop)
    {
        while (!line->m_stoped.empty() && line->m_stoped.top().second == this)
        {
            line->m_inter.insert(std::make_pair(line->m_stoped.top().first->get_ref(), line->m_stoped.top().first));
            line->m_stoped.pop();
        }
    }
    else
    {
        it = line->m_inter.begin();
        while (it != line->m_inter.end())
        {
            if (!get_line()->get_chan(it->second->get_act()[0])->get_use() ||
                    !get_line()->get_chan(it->second->get_act()[1])->get_use() ||
                    (!it->second->get_pow(PW) && !it->second->get_type(ATTACH)))
            {
                line->m_stoped.push(std::make_pair(it->second, this));
                it = line->m_inter.erase(it);
            }
            else
                it++;
        }
    }
}

void              Movable::apply(Object *from, ChanPropriety *prop, std::pair<float, float> &vct, std::pair<float, unsigned int> &chan)
{
    if (prop->get_type(MV))
    {
        m_moveLine.m_move.first += chan.first * vct.first;
        m_moveLine.m_move.second += chan.first * vct.second;
    }
    else
    {
        if (m_moveLine.m_change.find(chan.second) == m_moveLine.m_change.end())
            m_moveLine.m_change.insert(std::make_pair(chan.second, std::make_pair(std::make_pair(boost::unordered_map<Object*, float>(), 0),
                                                                                  get_line()->get_chan(chan.second)->get_value())));
        if (m_moveLine.m_change[chan.second].first.first.find(from) == m_moveLine.m_change[chan.second].first.first.end())
            m_moveLine.m_change[chan.second].first.first.insert(std::make_pair(from, 0));
        m_moveLine.m_change[chan.second].first.first[from] += chan.first;
        m_moveLine.m_change[chan.second].first.second += chan.first;
    }
}

bool              Movable::check_attach(MovableLine *line, ChanPropriety *prop)
{
    if (get_line()->get_chan(prop->get_act()[0])->get_value() > 0 &&
            get_line()->get_chan(prop->get_act()[1])->get_value() < 1)
    {
        if (!CAST(Decriptor*)(this) && CAST(Decriptor*)(line->m_parent))
        {
            line->m_parent->add_signal(ATTACH, static_cast<void*>(this));
            return (true);
        }
    }
    return (false);
}

void              Movable::interact_with(MovableLine *line, ChanPropriety *prop)
{
    std::pair<float, float>         vct;
    std::pair<float, unsigned int>  chan;
    unsigned int                    tmp[2];
    float                           lentmp;

    vct = line->m_vct;
    if (prop->get_type(ATTACH) && check_attach(line, prop))
        return ;
    if (prop->get_type(OTH))
    {
        vct.first *= -1;
        vct.second *= -1;
    }
    if ((tmp[0] = line->m_parent->get_line()->get_chan(prop->get_act()[0])->get_value()) &&
            (tmp[1] = get_line()->get_chan(prop->get_act()[1])->get_value()))
    {
        chan.first = tmp[0] + tmp[1];
        chan.first *= prop->get_pow(PW) / 100;
        chan.first *= prop->get_type(RPLS) ? -1 : 1;
        lentmp = (prop->get_pow(DST) - line->m_len) / prop->get_pow(DST);
        chan.first *= lentmp * 3.14 / 4;
        chan.second = prop->get_type(OTH) ? prop->get_act()[1] : prop->get_act()[0];
        if (prop->get_type(OTH))
            apply(line->m_parent, prop, vct, chan);
         else
            line->m_parent->apply(this, prop, vct, chan);
    }
}

void            Movable::get_interact(MovableLine *move)
{
    CHANPLIST::iterator                 it;

    move->m_vct.first = m_pos.first - move->m_parent->get_pos().first;
    move->m_vct.second = m_pos.second - move->m_parent->get_pos().second;
    move->m_vct.first += ((rand() % 100) - 50) / 200.0;
    move->m_vct.second += ((rand() % 100) - 50) / 200.0;
    move->m_len = move->m_vct.first * move->m_vct.first;
    move->m_len += move->m_vct.second * move->m_vct.second;
    move->m_len = sqrt(move->m_len);
    if (move->m_len)
    {
        move->m_vct.first /= move->m_len;
        move->m_vct.second /= move->m_len;
        for (it = move->m_inter.begin();it != move->m_inter.end(); it++)
        {
            if (move->m_len < it->second->get_pow(DST))
                interact_with(move, it->second);
        }
    }
}

void            Movable::get_move_line(MovableLine *move, Object *from)
{
    filter(move, true);
    if (move->m_inter.size() && from != this)
        get_interact(move);
    filter(move, false);
    if (m_parent && m_parent != from && CAST(Movable*)(m_parent))
    {
        filter(move, true);
        if (move->m_inter.size())
            CAST(Movable*)(m_parent)->get_move_line(move, this);
        filter(move, false);
    }
}
