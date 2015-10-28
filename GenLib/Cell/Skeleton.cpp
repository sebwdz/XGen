
#include        <cmath>
#include        <iostream>
#include        <cstdlib>
#include        <algorithm>
#include        "Cell/Skeleton.hpp"

Skeleton::Skeleton()
{
    m_pos.first = 0;
    m_pos.second = 0;
}

Skeleton::~Skeleton()
{

}

void        Skeleton::set_pos(std::pair<float, float> pos)
{
    m_pos = pos;
}

void        Skeleton::add_skeleton(Skeleton *skel)
{
    if (!m_son.size())
    {
        m_pos.first = 0;
        m_pos.second = 0;
    }
    m_pos.first += skel->m_pos.first;
    m_pos.second += skel->m_pos.second;
    m_son.push_back(skel);
}

float      Skeleton::get_angle(std::pair<float, float> pt)
{
    std::pair<float, float> vct;
    float               tmp;
    float               res;

    vct = m_pos;
    vct.first -= pt.first;
    vct.second -= pt.second;
    tmp = vct.first * vct.first + vct.second * vct.second;
    tmp = sqrt(tmp);
    if (tmp)
        res = acos(vct.first / tmp);
    else
        return (0);
    res *= 180.0 /  M_PI;
    if (vct.second < 0.0)
        res = 360.0 - res;
    return (res);
}

void        Skeleton::make()
{

    std::list<Skeleton*>::iterator  it;
    POINT_LIST::iterator            pt;

    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        for (pt = (*it)->get_begin(); pt != (*it)->get_end(); pt++)
            m_pt.push_back(*pt);
    }
}

void    Skeleton::cal_angle(AN_POINT_LIST &lst)
{
    POINT_LIST::iterator    it;
    std::pair<float, std::pair<float, float> >    value;

    for (it = m_pt.begin(); it != m_pt.end(); it++)
    {
        value.second = *it;
        value.first = get_angle(*it);
        lst.push_back(value);
    }
    m_pt.clear();
}

bool                    Skeleton::sort_skel(std::pair<float, std::pair<float, float> > &first,
                                      std::pair<float, std::pair<float, float> > &second)
{
    if (second.first < first.first ||
            (second.first == first.first &&
             second.second.first < first.second.first))
        return (false);
    return (true);
}

float      Skeleton::crossProduct(std::pair<float, float> pt, std::pair<float, float> be, std::pair<float, float> en)
{
    float                  res;

    res = (pt.first - be.first) * (en.second - be.second);
    res -= (en.first - be.first) * (pt.second - be.second);
    return (res);
}

AN_POINT_LIST::iterator Skeleton::get_begin_pt(AN_POINT_LIST &lst)
{
    AN_POINT_LIST::iterator it;
    AN_POINT_LIST::iterator most;

    most = lst.end();
    for (it = lst.begin(); it != lst.end(); it++)
    {
        if (most == lst.end() || most->second.first <= it->second.first)
        {
            if (most != lst.end() && most->second.first == it->second.first &&
                    most->second.second < it->second.second)
                continue;
            most = it;
        }
    }
    return (most);
}

void        Skeleton::get_outline()
{
    AN_POINT_LIST            lst;
    AN_POINT_LIST::iterator  it;
    AN_POINT_LIST::iterator  bg;
    POINT_LIST::iterator    last;
    POINT_LIST::iterator    prev;

    cal_angle(lst);
    lst.sort(&Skeleton::sort_skel);
    it = get_begin_pt(lst);
    m_pt.push_back((it++)->second);
    if (it == lst.end())
        it = lst.begin();
    bg = it;
    m_pt.push_back((it++)->second);
    prev = m_pt.end();
    prev--;
    last = prev--;
    do
    {
        it = it == lst.end() ? lst.begin() : it;
        while (m_pt.size() > 2 && crossProduct(it->second, *prev, *last) >= 0)
        {
            m_pt.pop_back();
            last = prev--;
        }
        m_pt.push_back(it->second);
        prev = last++;
    } while (it++ != bg);
    m_pt.pop_back();
    m_pt.pop_front();
    m_pt.pop_front();
}

void        Skeleton::finish()
{
    std::pair<float, float>             tmp;
    int                             add;

    if (!m_son.size())
    {
        add = rand() % 30;
        for (int it = 0; it < 5; it++)
        {
            tmp.first = 3.0 * cos(((360 / 5) * it + add) * 3.14 / 180);
            tmp.second = 3.0 * sin(((360 / 5) * it + add) * 3.14 / 180);
            tmp.first += m_pos.first;
            tmp.second += m_pos.second;
            m_pt.push_back(tmp);
        }
    }
    else
    {
        m_pos.first /= (int)m_son.size();
        m_pos.second /= (int)m_son.size();
        make();
        get_outline();
    }
}

void        Skeleton::clear()
{
    m_son.clear();
    m_pt.clear();
}

POINT_LIST::iterator  Skeleton::get_begin()
{
    return (m_pt.begin());
}

POINT_LIST::iterator  Skeleton::get_end()
{
    return (m_pt.end());
}

int                     Skeleton::get_size()
{
    return (m_pt.size());
}

std::pair<float, float> &Skeleton::get_pos()
{
    return (m_pos);
}
