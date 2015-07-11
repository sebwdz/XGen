#ifndef GENTICALPOOL_HPP_
#define GENTICALPOOL_HPP_

#include        <boost/thread.hpp>
#include        "GeneticalAlgo.hpp"

class           GeneticalPool : public GeneticalAlgo
{
public:
    GeneticalPool(GeneticObj *parent = 0);
    virtual ~GeneticalPool();

    void        make_pool();
    void        check_state();

    void        set_size(int size);
    void        set_pool_len(int len);
    void        set_pool_height(int height);
    void        set_continue(bool cnt);
    void        set_engine(SMART(VirtualMachine) engine);
    void        set_propriety(SMART(GeneticPropriety) propriety = SMART(GeneticPropriety)());

    int         get_pool_len();
    int         get_pool_height();
    bool        get_start();

    void        exec_thread(int cycle, int trmt);
    void        exec(int cycle, int trmt);
    void        dispatch();

    void        save(std::ofstream &file);
    void        load(std::ifstream &file);

private:

    std::vector<SMART(GeneticalPool)>               m_pool;
    int                                             m_poolLen;
    int                                             m_height;
    boost::thread                                   m_thread;
    bool                                            m_start;
};

#endif // GENTICALPOOL_HPP
