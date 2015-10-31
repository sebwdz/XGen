#ifndef GENETICBLOCK_HPP
#define GENETICBLOCK_HPP

#include      <boost/unordered_map.hpp>
#include      "GeneticalNode.hpp"

typedef class Chanel Chanel;
#define     USE_LIST        boost::unordered_map<unsigned int, Chanel*>

class     GeneticBlock : public GeneticObj
{
public:
  GeneticBlock();
  ~GeneticBlock();

  void          set_obj(SMART(GeneticObj) obj);

  SMART(GeneticObj) get_obj();
  USE_LIST      &get_chan();

  virtual SMART(ObjClass)    copy(SMART(ObjClass) cp = SMART(ObjClass)());

  void        load(std::ifstream &stream);
  void        save(std::ofstream &stream);

private:
  USE_LIST                m_chan;
  SMART(GeneticObj)       m_obj;
};

#endif // GENETICBLOCK_HPP
