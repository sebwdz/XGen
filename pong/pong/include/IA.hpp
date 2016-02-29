#ifndef IA_HPP
#define IA_HPP

# include               <boost/thread.hpp>
# include               "include/Player.hpp"
# include               "Cell/Brain.hpp"
#include                        "../../GenLibTester/include/BrainView.hpp"

class                   IAPlayer : public Player
{
public:
    IAPlayer(std::string const &file);
    ~IAPlayer();

    void                UpdateView();
    void                exec();
    void                show();

private:
    Object              *make_sensor(unsigned int, boost::shared_ptr<GeneticalNode>);
    Object              *make_actor(unsigned int, boost::shared_ptr<GeneticalNode>);

private:
    Brain               *m_brain;
    BrainView           m_view;
    boost::mutex        m_mutex;
    std::vector<Object*>    m_sensor;
    std::vector<Object*>    m_actor;
};

#endif // IA_HPP
