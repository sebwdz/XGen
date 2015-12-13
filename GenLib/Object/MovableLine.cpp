
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
  int                                 range[2] = {0};
  CHANPLIST::iterator                 it;

  for (it = m_parent->get_line()->get_begin_prop();
       it != m_parent->get_line()->get_end_prop(); it++)
    {
      if (it->second->get_pow(PW) || it->second->get_type(ATTACH) ||
          it->second->get_type(LINK) || it->second->get_type(COMIN))
        {
          if (it->second->get_pow(DST) > range[1])
            range[1] = it->second->get_pow(DST);
          if (range[0] == 0 || it->second->get_pow(DST) < range[0])
            range[0] = it->second->get_pow(DST);
        }
    }
  m_range.first = range[0];
  m_range.second = range[1];
}

void            MovableLine::change_chan(unsigned int ref, sMovableChan *move)
{
  boost::unordered_map<Object*, float>::iterator  it;
  boost::unordered_map<Object*, float>::iterator  end;
  LineDecript                                     *line;
  float                                           tmp;
  float                                           all;

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
          line->get_chan(ref)->set_value(tmp + line->get_chan(ref)->get_value());
          it->second = 0;
        }
      it++;
    }
  m_parent->get_line()->get_chan(ref)->set_value(m_parent->get_line()->get_chan(ref)->get_value() - all);
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

void            MovableLine::interact_with(class Movable *obj, ChanPropriety *prop)
{
  std::pair<float, float>         vct;
  std::pair<float, unsigned int>  chan;
  unsigned int                    tmp[2];
  float                           lentmp;

  vct = m_vct;
  if (prop->get_type(ATTACH) || prop->get_type(LINK) || prop->get_type(COMIN))
    {
      check_attach(obj, prop);
      return ;
    }
  if (prop->get_type(OTH))
    {
      vct.first *= -1;
      vct.second *= -1;
    }
  if ((tmp[0] = prop->get_chan()->get_value()) &&
      (tmp[1] = obj->get_line()->get_value(prop->get_act()[1])))
    {
      chan.first = tmp[0] + tmp[1];
      chan.first *= prop->get_pow(PW) / 100;
      chan.first *= prop->get_type(RPLS) ? -1 : 1;
      lentmp = (prop->get_pow(DST) - m_len) / prop->get_pow(DST);
      chan.first *= (lentmp * lentmp) * (3.14 / 4);
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
      if (m_len < m_range.second || m_parent == obj->get_parent() || obj == m_parent->get_parent())
        {
          m_vct.first /= m_len;
          m_vct.second /= m_len;
          if (m_parent == obj->get_parent() || obj == m_parent->get_parent() || m_len < 1)
            m_len = 1;
          for (it = m_parent->get_line()->get_begin_prop(); it != m_parent->get_line()->get_end_prop(); it++)
            {
              if (it->second->get_chan() &&
                  it->second->get_pow(DST) >= m_len &&
                  it->second->get_pow(MINDST) <= m_len)
                interact_with(obj, it->second);
            }
        }
    }
}

void            MovableLine::apply(Movable *from, ChanPropriety *prop, std::pair<float, float> &vct, std::pair<float, unsigned int> &chan)
{
  sMovableChan            *move;
  float                   tmp;
  CHAN_MOVELIST::iterator it;

  if (prop->get_type(MV))
    {
      m_move.first += vct.first * chan.first;
      m_move.second += vct.second * chan.first;
    }
  else
    {
      if ((it = m_change.find(chan.second)) == m_change.end())
        {
          move = new sMovableChan;
          move->life = 0;
          move->total = 0;
          m_change.insert(std::make_pair(chan.second, move));
        }
      else
        move = it->second;
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
      move->have = m_parent->get_line()->get_chan(chan.second)->get_value();
    }
}

bool              MovableLine::check_attach(Object *obj, ChanPropriety *prop)
{
  if (obj->get_line()->get_value(prop->get_act()[0]) > 0 &&
      obj->get_line()->get_value(prop->get_act()[1]) < 1)
    {
      if (prop->get_type(ATTACH) && !(obj->get_type() & TYPE_DECRIPTOR) && m_parent->get_type() & TYPE_DECRIPTOR)
        {
          m_parent->add_signal(ATTACH, static_cast<void*>(obj));
          return (true);
        }
      else if (prop->get_type(LINK) && obj->get_type() & TYPE_MODULE && m_parent->get_type() & TYPE_MODULE)
        {
          m_parent->add_signal(LINK, static_cast<void*>(obj));
          return (true);
        }
      else if (prop->get_type(COMIN))
        {
          m_parent->add_signal(COMIN, static_cast<void*>(obj));
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

std::pair<int, int>     &MovableLine::get_range()
{
  return (m_range);
}
