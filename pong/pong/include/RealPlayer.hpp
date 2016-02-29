#ifndef REALPLAYER_HPP
#define REALPLAYER_HPP

# include               "Player.hpp"

class                   RealPlayer : public Player
{
public:
    RealPlayer(std::string const&);
    ~RealPlayer();

    void                exec();
};

#endif // REALPLAYER_HPP
