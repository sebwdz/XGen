
#include                        <SFML/System/Thread.hpp>
#include                        "include/IA.hpp"
#include                        "include/RealPlayer.hpp"

Player::Player()
{
    m_type = PLAYER;
    m_ball = NULL;
}

Player::~Player()
{

}

Player                          *Player::get_player(PlayerType type, const std::string &name)
{
    if (type == IA)
        return (new IAPlayer(name));
    return (new RealPlayer(name));
}

void                            Player::set_pos(std::pair<float, float> const &pos)
{
    m_pos = pos;
}

void                            Player::move(float y)
{
    m_pos.second += y;
    if (m_pos.second >= 245 - 25)
        m_pos.second = 220;
    else if (m_pos.second <= -245 + 25)
        m_pos.second = -220;
}

Player::PlayerType                      Player::get_type() const
{
    return (m_type);
}

void                                    Player::set_ball(Ball *ball)
{
    m_ball = ball;
}

void                            Player::start()
{
    m_thread = new sf::Thread(&Player::exec, this);
    m_thread->launch();
}

std::pair<float, float>         &Player::get_pos()
{
    return (m_pos);
}
