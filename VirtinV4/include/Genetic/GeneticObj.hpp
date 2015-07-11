#ifndef GENETICOBJ_HPP
#define GENETICOBJ_HPP

#include    <vector>
#include    <obj.hpp>

#define        VAR_LIST                                 std::list<std::pair<std::string, unsigned int> >

typedef struct                                          GeneticPropriety
{
    std::vector<std::pair<int, int> >                   range;
    int                                                 height;
    int                                                 len;
} GeneticPropriety;

class                   GeneticObj : public ObjClass
{
public:
    GeneticObj(GeneticObj *parent = 0);
    virtual ~GeneticObj();

    virtual void        set_propriety(SMART(GeneticPropriety) propriety = SMART(GeneticPropriety)());

    SMART(GeneticPropriety)   get_propriety();

    unsigned int        get_alea_range();
    int                 get_len();
    bool                alea(int range, int target);

    virtual void        save(std::ofstream &file);
    virtual void        load(std::ifstream &file);
protected:

    boost::shared_ptr<GeneticPropriety>    m_propriety;
    int                 m_len;
};

#endif // GENETICOBJ_HPP
