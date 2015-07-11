#ifndef CHANNELCLASS_HPP_INCLUDED
#define CHANNELCLASS_HPP_INCLUDED

# include   <map>

class   ChannelList
{
public:
        ChannelList();
        ~ChannelList();

        void            add_channel(unsigned int id);
        void            clear_channel(unsigned int id);
        unsigned int    get_channel_value(unsigned int channel);
        void            set_channel_value(unsigned int channel, unsigned int value);
private:

    std::map<unsigned int, unsigned int>  m_channel;
};

#endif // CHANNELCLASS_HPP_INCLUDED
