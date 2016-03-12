#ifndef BRAIN_HPP
#define BRAIN_HPP

#include    <map>
#include    "Network/Sender.hpp"
#include    "Network/Receiver.hpp"
#include    "Module.hpp"

class       Brain : public ModuleClass
{
public:
    Brain();
    virtual ~Brain();

    virtual void                    exec();
    void                            set_dna(SMART(GeneticalNode) node);
    void                            send_interaction(Object* from, GeneticalNode *prop);
    void                            exec_interactions(Package *pack);

private:
    Sender                          m_sender;
    Receiver                        m_receiver;
    std::vector<Package*>           m_send;
};

#endif // BRAIN_HPP
