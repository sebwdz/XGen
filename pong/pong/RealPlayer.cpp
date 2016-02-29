
#include                <iostream>
#include                "include/RealPlayer.hpp"

RealPlayer::RealPlayer(const std::string &name) : Player()
{
    m_name = name;
    std::cout << "New Real Player with name => " << m_name << std::endl;
}

RealPlayer::~RealPlayer()
{

}

void            RealPlayer::exec()
{

}
