
#include        "Decriptor/Decriptor.hpp"

MovableLine::MovableLine()
{

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

  for (it = 0; it < sons.size(); it++)
    {
      if (sons[it]->get_son_ref(LIMIT)->get_value()._f &&
          !sons[it]->get_son_ref(LIMIT)->get_son_ref(0)->get_value()._f)
        continue;
      if (sons[it]->get_son_ref(PW)->get_value()._f || sons[it]->get_son_ref(TYPE)->get_value()._f == ATTACH ||
          sons[it]->get_son_ref(TYPE)->get_value()._f == LINK || sons[it]->get_son_ref(TYPE)->get_value()._f == COMIN)
        {
          dst = sons[it]->get_son_ref(DST)->get_value()._f;
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
          value = line->get_chan(move->path)->get_value();
          value._f += tmp;
          line->get_chan(move->path)->set_value(value);
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

void            MovableLine::interact_with(class Movable *obj, GeneticalNode *prop)
{
  std::pair<float, float>                 vct;
  float                                   chan;
  float                                   type;
  std::pair<float, GeneticalNode*>        node;
  GeneticalNode*                          tmp[2];

  vct = m_vct;
  type = prop->get_son_ref(TYPE)->get_value()._f;
  if (type == ATTACH || type == LINK || type == COMIN)
    {
      check_attach(obj, prop);
      return ;
    }
  if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
    {
      vct.first *= -1;
      vct.second *= -1;
    }
  tmp[1] = obj->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(1).get()).get();
  tmp[0] = m_parent->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(0).get()).get();
  if (tmp[0]->get_value()._f && tmp[1]->get_value()._f)
    {
      chan = tmp[0]->get_value()._f + tmp[1]->get_value()._f;
      chan *= prop->get_son_ref(PW)->get_value()._f;
      reduce(chan, prop);
      chan *= prop->get_son_ref(DIR)->get_value()._f == RPLS ? -1 : 1;
      node.first = chan / 100;
      if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
          node.second = prop->get_son_ref(ACT)->get_son_ref(1).get();
      else
        node.second = prop->get_son_ref(ACT)->get_son_ref(0).get();
      if (prop->get_son_ref(TARGET)->get_value()._f == OTH)
          obj->get_move_line()->apply(m_parent, prop, vct, node);
      else
          apply(obj, prop, vct, node);
    }
}

void            MovableLine::interact(Movable *obj)
{
  unsigned int                      it;
  std::vector<SMART(GeneticalNode)> &vct = m_parent->get_line()->get_interaction()->get_son();

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
              if (vct[it]->get_son_ref(LIMIT)->get_value()._f &&
                  !vct[it]->get_son_ref(LIMIT)->get_son_ref(0)->get_value()._f)
                continue;
              if (vct[it]->get_son_ref(DST)->get_value()._f >= m_len &&
                  vct[it]->get_son_ref(MINDST)->get_value()._f <= m_len)
                interact_with(obj, vct[it].get());
            }
        }
    }
}

void            MovableLine::apply(Movable *from, GeneticalNode *prop, std::pair<float, float> &vct, std::pair<float, GeneticalNode*> &chan)
{
  sMovableChan            *move;
  float                   tmp;
  CHAN_MOVELIST::iterator it;
  GeneticalNode           *node;
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
      node = m_parent->get_line()->get_chan(chan.second).get();
      if ((it = m_change.find(node)) == m_change.end())
        {
          move = new sMovableChan;
          move->life = 0;
          move->total = 0;
          m_change.insert(std::make_pair(node, move));
        }
      else
        move = it->second;
      move->path = chan.second;
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

bool              MovableLine::check_attach(Object *obj, GeneticalNode *prop)
{
  float           tmp[2];
  unsigned int    type;
  nodeValue       val;
  bool            res;

  tmp[1] = obj->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(1).get())->get_value()._f;
  tmp[0] = obj->get_line()->get_chan(prop->get_son_ref(ACT)->get_son_ref(0).get())->get_value()._f;
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
}

Movable*        MovableLine::get_parent()
{
  return (m_parent);
}

std::pair<int, int>     &MovableLine::get_range()
{
  return (m_range);
}
