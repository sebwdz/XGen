#ifndef MONITOR_HPP
#define MONITOR_HPP

#include        <sys/time.h>

class           Monitor
{
public:
        ~Monitor() { }
        static Monitor      *get_instance() { static Monitor m; return (&m); }
        unsigned int        get_instru() { return (m_instru); }
        float               get_time() { return (m_time); }
        void                add_instru() { m_instru++; }
        void                begin_instru() { gettimeofday(&m_use[0], NULL); }
        void                end_instru() { float tmp; gettimeofday(&m_use[1], NULL);  tmp = (float)((m_use[1].tv_usec / 1000.0) - (m_use[0].tv_usec / 1000.0)); if (tmp > 0) m_time += tmp;}
        void                reset_instru() { m_instru = 0; m_time = 0; }
private:
        Monitor() { m_instru = 0; m_time = 0; }
        unsigned int        m_instru;
        float               m_time;
        struct timeval      m_use[2];
};

#endif // MONITOR_HPP
