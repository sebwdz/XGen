
#include            "Decriptor/Opt.hpp"
#include            "Decriptor/ChanelPropriety.hpp"

ChanPropriety::ChanPropriety()
{
  m_pow = 0;
  m_dist = 0;
  m_act[0] = 0;
  m_act[1] = 0;
  m_dir = false;
  m_type = false;
  m_atr = false;
  m_link = false;
  m_comin = false;
  m_attach = false;
  m_chan = NULL;
}

ChanPropriety::~ChanPropriety()
{

}

void            ChanPropriety::set_ref(unsigned int ref)
{
  m_ref = ref;
}

void            ChanPropriety::set_type(unsigned int type)
{
  if (type == MV)
    m_type = true;
  else if (type == CHNG)
    m_type = false;
  else if (type == TO)
    m_dir = true;
  else if (type == OTH)
    m_dir = false;
  else if (type == RPLS)
    m_atr = false;
  else if (type == ATR)
    m_atr = true;
  else if (type == ATTACH)
    m_attach = true;
  else if (type == LINK)
    m_link = true;
  else if (type == COMIN)
    m_comin = true;
}

void            ChanPropriety::set_pow(unsigned int type, float value)
{
  if (type == DST)
    m_dist = value;
  else if (type == PW)
    m_pow = value;
}

void            ChanPropriety::set_chan(Chanel *chan)
{
  m_chan = chan;
}

void            ChanPropriety::set_res(float res)
{
  m_res = res;
}

void            ChanPropriety::set_act(unsigned int type, unsigned int chan)
{
  if (type == TO)
    m_act[0] = chan;
  else if (type == OTH)
    m_act[1] = chan;
}

unsigned int    ChanPropriety::get_ref() const
{
  return (m_ref);
}

bool            ChanPropriety::get_type(unsigned int type) const
{
  if (type == ATTACH && m_attach)
    return (true);
  else if (type == LINK && m_link)
    return (true);
  else if (type == LINK)
    return (false);
  else if (type == ATTACH)
    return (false);
  else if (type == COMIN && m_comin)
    return (true);
  else if (type == COMIN)
    return (false);
  else if (type == MV && m_type)
    return (true);
  else if (type == CHNG && !m_type)
    return (true);
  else if (type == TO && m_dir)
    return (true);
  else if (type == OTH && !m_dir)
    return (true);
  else if (type == ATR && m_atr)
    return (true);
  else if (type == RPLS && !m_atr)
    return (true);
  return (false);
}

float           ChanPropriety::get_pow(unsigned int type) const
{
  if (type == DST)
    return (m_dist);
  else if (type == PW)
    return (m_pow);
  return (0);
}

unsigned int    *ChanPropriety::get_act()
{
  return (m_act);
}

Chanel          *ChanPropriety::get_chan() const
{
  return (m_chan);
}

float           ChanPropriety::get_res() const
{
  return (m_res);
}
