
#include        "Decriptor/LineDecrip.hpp"

LineDecript::LineDecript()
{
  m_global = SMART(GeneticalNode)(new GeneticalNode());
  m_shared = SMART(GeneticalNode)(new GeneticalNode());
  m_prop = SMART(GeneticalNode)(new GeneticalNode());
}

LineDecript::~LineDecript()
{
}

void                LineDecript::get_ready()
{
  m_signals.clear();
}

void                LineDecript::add_signal(unsigned int value, void *ptr)
{
  m_signals.push_back(std::make_pair(value, ptr));
}

SIGNALS_LIST        &LineDecript::get_signals()
{
  return (m_signals);
}

float            LineDecript::get_value(unsigned int ref, bool use)
{
  SMART(GeneticObj)  res;

  if (!(res = m_global->get_ass(ref, false)))
    return (0);
  return (res->get_value()._f);
}

void                    LineDecript::shared_to_line(LineDecript *line)
{
  USE_LIST::iterator  it;

  for (it = line->m_shared->get_ass().begin(); it != line->m_shared->get_ass().end(); it++)
      m_global->set_ass(it->first, it->second->copy());
}

SMART(GeneticalNode)    LineDecript::get_chan()
{
  return (m_global);
}

SMART(GeneticalNode)    LineDecript::get_shared()
{
  return (m_shared);
}

SMART(GeneticalNode)    LineDecript::get_interaction()
{
  return (m_prop);
}

SMART(GeneticalNode)             LineDecript::get_chan(unsigned int key)
{
  return (m_global->get_ass(key));
}

SMART(GeneticalNode)             LineDecript::get_chan(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)> &vct = node->get_son();
  SMART(GeneticalNode)                 chan;

  chan = m_global;
  for (unsigned  int it = 0; it < vct.size(); it++) {
      if (vct[it]->get_type() == EMPTY_CHAN)
        chan = chan->get_ass(vct[it]->get_value()._ui);
      else if (vct[it]->get_type() == VALUE)
        chan = chan->get_son_ref((unsigned int)vct[it]->get_value()._f);
    }
  return (chan);
}

USE_LIST::iterator  LineDecript::get_begin()
{
  return (m_global->get_ass().begin());
}


USE_LIST::iterator  LineDecript::get_end()
{
  return (m_global->get_ass().end());
}
