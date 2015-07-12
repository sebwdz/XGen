#ifndef SQUELETON_HPP
#define SQUELETON_HPP

#include    <list>

#define     POINT_LIST      std::list<std::pair<float, float> >
#define     AN_POINT_LIST   std::list<std::pair<float, std::pair<float, float> > >

class                       Skeleton
{
public:
    Skeleton();
    virtual ~Skeleton();

    void                    set_pos(std::pair<float, float> pos);
    void                    add_skeleton(Skeleton *skel);
    void                    finish();
    void                    clear();
    POINT_LIST::iterator    get_begin();
    POINT_LIST::iterator    get_end();
    int                     get_size();
    void                    make();
    float                   get_angle(std::pair<float, float> pt);
    void                    cal_angle(AN_POINT_LIST &lst);
    float                   crossProduct(std::pair<float, float> pt, std::pair<float, float> be,
                                       std::pair<float, float> en);
    AN_POINT_LIST::iterator get_begin_pt(AN_POINT_LIST &lst);
    void                    get_for_one(Skeleton *skel);
    void                    get_outline();
    std::pair<float, float> &get_pos();
    static bool             sort_skel(std::pair<float, std::pair<float, float> > &first,
                                          std::pair<float, std::pair<float, float> > &second);


protected:

    std::pair<float, float> m_pos;
    std::list<Skeleton*>    m_son;
    POINT_LIST              m_pt;
    float                   m_angle;
};

#endif // SQUELETON_HPP
