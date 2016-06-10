#ifndef BRAIN_HPP
#define BRAIN_HPP

#include    <map>
#include    "Module.hpp"

class       Brain : public ModuleClass
{
public:
    Brain();
    virtual ~Brain();

    virtual void                    exec();
    void                            set_dna(SMART(GeneticalNode) node);
    //void                            send_interaction(Object* from, GeneticalNode *prop);
    //void                            exec_interactions(Package *pack);

private:
    //std::vector<Package*>           m_send;
};

#endif // BRAIN_HPP
