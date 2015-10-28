#ifndef MONITOR_HPP
#define MONITOR_HPP

#include        <sys/time.h>
#include        <boost/unordered_map.hpp>

#define         MN_ALL     0
#define         MN_INSTR   1

struct          S_Monitor
{
    unsigned int        _int;
    float               _time;
    struct timeval      _use[2];
    std::string         _name;
};

class           Monitor
{
public:
        ~Monitor() {

        }
        static Monitor      *get_instance() { static Monitor m; return (&m); }
        unsigned int        get_val(unsigned int str) {
            S_Monitor *m = &m_monitor[str];
            return (m->_int);
        }
        float               get_time(unsigned int str) {
            S_Monitor *m = &m_monitor[str];
            return (m->_time);
        }
        void                add_val(unsigned int str) {
            S_Monitor *m = &m_monitor[str];
            m->_int++;
        }
        void                begin_time(unsigned int str) {
            S_Monitor *m = &m_monitor[str];
            gettimeofday(&m->_use[0], NULL);
        }
        void                end_time(unsigned int str) {
            float tmp;
            S_Monitor *m = &m_monitor[str];
            gettimeofday(&m->_use[1], NULL);
            tmp = (float)((m->_use[1].tv_usec) - (m->_use[0].tv_usec)) / 1000 + (float)((m->_use[1].tv_sec) - (m->_use[0].tv_sec)) * 1000;
            if (tmp > 0)
                m->_time += tmp;
            else
                m->_time += 0.000001;
        }
        void                reset_val(unsigned int str) {
            S_Monitor *m = &m_monitor[str];
            m->_int = 0;
            m->_time = 0;
        }
private:
        Monitor() { m_monitor.push_back(S_Monitor());
                    m_monitor.back()._int = 0;
                    m_monitor.back()._time = 0;
                    m_monitor.back()._name = "all";
                    m_monitor.push_back(S_Monitor());
                    m_monitor.back()._int = 0;
                    m_monitor.back()._time = 0;
                    m_monitor.back()._name = "instrs";
                  }
        std::vector<S_Monitor>       m_monitor;
};

#endif // MONITOR_HPP
