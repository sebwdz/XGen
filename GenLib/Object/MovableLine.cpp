
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"

MovableLine::MovableLine()
{
    m_decriptor = NULL;
}

MovableLine::~MovableLine()
{

}

void            MovableLine::make()
{
    m_move.first = 0;
    m_move.second = 0;
    make_range();
}

void            MovableLine::make_range()
{
    int                               range[2] = {0};
    unsigned int                      it;
    float                             dst;
    std::vector<SMART(GeneticalNode)> &sons = m_parent->get_line()->get_interaction()->get_son();
    SMART(GeneticalNode)                param;

    for (it = 0; it < sons.size(); it++)
    {
        param = sons[it]->get_ass(Chanel::hash("_param"));
        if (param->get_son_ref(LIMIT)->get_value()._f &&
                param->get_son_ref(LIMIT)->get_son_ref(0)->get_value()._f <= 0)
            continue;
        if (can_interact(sons[it].get(), OTH))
        {
            dst = param->get_son_ref(DST)->get_value()._f;
            if (dst > range[1])
                range[1] = dst;
            if (range[0] == 0 || dst < range[0])
                range[0] = dst;
        }
    }
    m_range.first = range[0];
    m_range.second = range[1];
}

void            MovableLine::change_chan(GeneticalNode* ref, sMovableChan *move)
{
    boost::unordered_map<Object*, float>::iterator  it;
    boost::unordered_map<Object*, float>::iterator  end;
    LineDecript                                     *line;
    float                                           tmp;
    float                                           all;
    nodeValue                                       value;
    GeneticalNode                                   *node;

    it = move->obj.begin();
    end = move->obj.end();
    all = 0;
    tmp = 0;
    while (it != end)
    {
        if (it->second > 0 && move->total > 0)
        {
            line = it->first->get_line();
            if (move->total < move->have)
                tmp = (it->second / move->total) * move->total;
            else
                tmp = (it->second / move->total) * move->have;
            all += tmp;
            node = line->get_chan(move->path).get();
            value = node->get_value();
            value._f += tmp;
            node->set_value(value);
            it->second = 0;
        }
        it++;
    }
    value = ref->get_value();
    value._f -= all;
    ref->set_value(value);
    move->life = 0;
    move->total = 0;
    move->have = 0;
    move->obj.clear();
}

void            MovableLine::exec()
{
    std::pair<float, float>     pos;
    CHAN_MOVELIST::iterator     it;
    CHAN_MOVELIST::iterator     rm;
    std::vector<SMART(GeneticalNode)>   &inter = m_parent->get_line()->get_interaction()->get_son();

    /*pos = m_parent->get_pos();
    pos.first += m_move.first;
    pos.second += m_move.second;
    if (m_parent->get_type() & TYPE_MODULE)
        CAST(ModuleClass*)(m_parent)->change_pos(m_move);
    m_parent->set_pos(pos);
    */
    // Clean
    for (unsigned int it = 0; it < inter.size(); it++)
    {
        if (m_decriptor)
        {
            m_decriptor->get_fast()->get_ass(Chanel::hash("this"))->set_ref(inter[it]);
            m_decriptor->turn(inter[it]->get_ass(Chanel::hash("_clean")).get());
        }
    }
    /*
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
    }*/
}

void            MovableLine::reduce(float &chan, GeneticalNode *prop)
{
    unsigned int  type;
    float         val;
    float         lentmp;

    type = (unsigned int)prop->get_son_ref(REDUCE)->get_son_ref(0)->get_value()._f;
    val = prop->get_son_ref(REDUCE)->get_son_ref(1)->get_value()._f;
    if (type == AUTO)
    {
        lentmp = ((prop->get_son_ref(DST)->get_value()._f - m_len) / prop->get_son_ref(DST)->get_value()._f);
        chan *= (lentmp * lentmp) * (3.14 / 4);
    }
    else if (type == FIX)
        chan -= val  * (prop->get_son_ref(DST)->get_value()._f / 100);
    else
    {


    }
}

bool             MovableLine::can_interact(GeneticalNode *prop, unsigned int scope)
{
    std::vector<SMART(GeneticalNode)>       nodes = prop->get_son_ref(SCOPE)->get_son();

    if (!prop->get_son_ref(SCOPE)->get_value()._f)
        return (true);
    for (unsigned int it = 0; it < nodes.size(); it++)
    {
        if (nodes[it]->get_value()._f == scope)
            return (true);
    }
    return (false);
}

float           MovableLine::get_pow(LineDecript *line, GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    float       pow = 0;

    for (unsigned int it = 0; it < vct.size(); it++)
        pow += line->get_chan(vct[it].get())->get_value()._f;
    return (pow);
}

void            MovableLine::interact_with(class Movable *obj, SMART(GeneticalNode) prop)
{
    std::pair<float, float>                 vct;
    float                                   chan;
    float                                   type;
    std::pair<float, GeneticalNode*>        node;
    float                                   tmp[2];
    SMART(GeneticalNode)                    fast;

    vct = m_vct;
    type = prop->get_ass(Chanel::hash("_param"))->get_son_ref(TYPE)->get_value()._f;
    if (type != MANUAL)
        check_attach(obj, prop.get());
    else
    {
        if (!m_decriptor)
        {
            m_decriptor = new Decriptor(m_parent);
            m_decriptor->set_attach(true);
        }
        fast = m_decriptor->get_fast();
        fast->get_ass(Chanel::hash("__oth__"))->set_ref(obj->get_line()->get_chan());
        fast->get_ass(Chanel::hash("this"))->set_ref(prop);
        fast->get_ass(Chanel::hash("__vct__"))->get_son_ref(0)->get_value()._f = m_vct.first;
        fast->get_ass(Chanel::hash("__vct__"))->get_son_ref(1)->get_value()._f = m_vct.second;
        fast->get_ass(Chanel::hash("__vct__"))->get_son_ref(2)->get_value()._f = m_len;
        m_decriptor->turn(prop->get_ass(Chanel::hash("_exec")).get());
    }
            /*
    if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
    {
        vct.first *= -1;
        vct.second *= -1;
    }
    tmp[0] = get_pow(m_parent->get_line(), prop->get_son_ref(ACT)->get_son_ref(0)->get_son_ref(0).get());
    tmp[0] -= get_pow(m_parent->get_line(), prop->get_son_ref(ACT)->get_son_ref(0)->get_son_ref(1).get());
    tmp[1] = get_pow(obj->get_line(), prop->get_son_ref(ACT)->get_son_ref(1)->get_son_ref(0).get());
    tmp[1] -= get_pow(obj->get_line(), prop->get_son_ref(ACT)->get_son_ref(1)->get_son_ref(1).get());
    if (tmp[0] > 0 && tmp[1] > 0)
    {
        chan = tmp[0] + tmp[1];
        chan *= prop->get_son_ref(PW)->get_value()._f;
        reduce(chan, prop);
        chan *= prop->get_son_ref(DIR)->get_value()._f == RPLS ? -1 : 1;
        node.first = chan / 1000;
        if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
            node.second = prop->get_son_ref(ACT)->get_son_ref(1)->get_son_ref(0).get();
        else
            node.second = prop->get_son_ref(ACT)->get_son_ref(0)->get_son_ref(0).get();
        if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
            obj->get_move_line()->apply(m_parent, prop, vct, node);
        else
            apply(obj, prop, vct, node);
    }*/
}

void            MovableLine::interact(Movable *obj, unsigned int scope)
{
    unsigned int                      it;
    std::vector<SMART(GeneticalNode)> &vct = m_parent->get_line()->get_interaction()->get_son();
    SMART(GeneticalNode)                param;

    m_vct.first = obj->get_pos().first - m_parent->get_pos().first + (((rand() % 100) - 50) / 200.0);
    m_vct.second = obj->get_pos().second - m_parent->get_pos().second + (((rand() % 100) - 50) / 200.0);
    m_len = m_vct.first * m_vct.first + m_vct.second * m_vct.second;
    if (m_len > 0)
    {
        m_len = sqrt(m_len);
        if (m_len < m_range.second || m_parent == obj->get_parent() || obj == m_parent->get_parent())
        {
            m_vct.first /= m_len;
            m_vct.second /= m_len;
            if (m_parent == obj->get_parent() || obj == m_parent->get_parent() || m_len < 1)
                m_len = 1;
            for (it = 0; it < vct.size(); it++)
            {
                param = vct[it]->get_ass(Chanel::hash("_param"));
                if (!can_interact(param.get(), scope))
                    continue;
                if (param->get_son_ref(LIMIT)->get_value()._f &&
                        param->get_son_ref(LIMIT)->get_son_ref(0)->get_value()._f <= 0)
                    continue;
                if (param->get_son_ref(DST)->get_value()._f >= m_len &&
                        param->get_son_ref(MINDST)->get_value()._f <= m_len)
                    interact_with(obj, vct[it]);
            }
        }
    }
}

void            MovableLine::apply_change(Movable *from, std::pair<float, GeneticalNode*> &chan)
{
    sMovableChan                        *move;
    float                               tmp;
    GeneticalNode                       *node;
    CHAN_MOVELIST::iterator             it;
    std::vector<SMART(GeneticalNode)>   &nodes = chan.second->get_son();

    for (unsigned int uit = 0; uit < nodes.size(); uit++)
    {
        node = m_parent->get_line()->get_chan(nodes[uit].get()).get();
        if ((it = m_change.find(node)) == m_change.end())
        {
            move = new sMovableChan;
            move->life = 0;
            move->total = 0;
            m_change.insert(std::make_pair(node, move));
        }
        else
            move = it->second;
        move->path = nodes[uit].get();
        if (move->obj.find(from) == move->obj.end())
            move->obj.insert(std::make_pair(from, 0));
        tmp = 0;
        if (move->obj[from] < 0 && chan.first > 0 && chan.first > move->obj[from] * -1)
            tmp = chan.first + move->obj[from];
        else if (move->obj[from] > 0 && chan.first < 0)
        {
            if (move->obj[from] > chan.first - 1)
                tmp = chan.first + move->obj[from];
            else
                tmp = chan.first;
        }
        else if (chan.first > 0)
            tmp = chan.first;
        move->obj[from] += chan.first;
        move->total += tmp;
        move->have = node->get_value()._f;
    }
}

void            MovableLine::apply(Movable *from, GeneticalNode *prop, std::pair<float, float> &vct,
                                   std::pair<float, GeneticalNode*> &chan)
{
    nodeValue               val;

    if (prop->get_son_ref(LIMIT)->get_value()._f)
    {
        val = prop->get_son_ref(LIMIT)->get_son_ref(0)->get_value();
        val._f--;
        prop->get_son_ref(LIMIT)->get_son_ref(0)->set_value(val);
    }
    if (prop->get_son_ref(TYPE)->get_value()._f == MV)
    {
        m_move.first += vct.first * chan.first;
        m_move.second += vct.second * chan.first;
    }
    else
    {
        apply_change(from, chan);
    }
}

bool              MovableLine::check_attach(Object *obj, GeneticalNode *prop)
{
    float           tmp[2];
    unsigned int    type;
    nodeValue       val;
    bool            res;

    tmp[1] = obj->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(1).get())->get_value()._f;
    tmp[0] = obj->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(0).get())->get_value()._f;
    res = false;
    if(tmp[0] > 0 && tmp[1] < 1)
    {
        type = prop->get_son_ref(TYPE)->get_value()._f;
        if (type == ATTACH && !(obj->get_type() & TYPE_DECRIPTOR) && m_parent->get_type() & TYPE_DECRIPTOR)
        {
            m_parent->add_signal(ATTACH, static_cast<void*>(obj));
            res = true;
        }
        else if (type == LINK && obj->get_type() & TYPE_MODULE && m_parent->get_type() & TYPE_MODULE)
        {
            m_parent->add_signal(LINK, static_cast<void*>(obj));
            res = true;
        }
        else if (type == COMIN)
        {
            m_parent->add_signal(COMIN, static_cast<void*>(obj));
            res = true;
        }
    }
    if (res)
    {
        if (prop->get_son_ref(LIMIT)->get_value()._f)
        {
            val = prop->get_son_ref(LIMIT)->get_son_ref(0)->get_value();
            val._f--;
            prop->get_son_ref(LIMIT)->get_son_ref(0)->set_value(val);
        }
    }
    return (res);
}


void            MovableLine::set_parent(Movable *parent)
{
    m_parent = parent;
    if (m_decriptor)
        m_decriptor->set_parent(parent);
}

Movable*        MovableLine::get_parent()
{
    return (m_parent);
}

std::pair<int, int>     &MovableLine::get_range()
{
    return (m_range);
}
