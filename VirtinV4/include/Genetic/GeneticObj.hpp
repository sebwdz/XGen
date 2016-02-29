#ifndef GENETICOBJ_HPP
#define GENETICOBJ_HPP

#include    <vector>
#include    <list>
#include    <obj.hpp>

#define        VAR_LIST                                 std::list<std::pair<std::string, unsigned int> >

typedef union u_nodeValue {
  float         _f;
  unsigned char _uc;
  unsigned int  _ui;
} nodeValue;

class                   GeneticObj : public ObjClass
{
public:
    GeneticObj(GeneticObj *parent = 0);
    virtual ~GeneticObj();

    int                     get_type();
    void                    set_type(int type);
    void                    set_ref(SMART(GeneticObj) ref);

    void                    set_value(nodeValue value);
    nodeValue               &get_value();
    SMART(GeneticObj)       get_ref();

    virtual void            save(std::ofstream &file) = 0;
    virtual void            load(std::ifstream &file) = 0;
protected:

    nodeValue           m_value;
    SMART(GeneticObj)   m_ref;

};

#endif // GENETICOBJ_HPP
