#ifndef PLAYER_HPP
#define PLAYER_HPP

# include               <string>
#include                <SFML/System/Thread.hpp>

typedef class Ball Ball;

class                   Player
{
public:
    enum                PlayerType {
        IA, PLAYER
    };

public:
    Player();
    virtual ~Player();
    void                start();
    virtual void        exec() = 0;
    virtual void        show() { }
    void                move(float);
    void                set_pos(std::pair<float, float> const &pos);
    PlayerType          get_type() const;
    void                set_ball(Ball*);

    static Player       *get_player(PlayerType, std::string const& name);

    std::pair<float, float> &get_pos();
protected:
    std::string         m_name;
    PlayerType          m_type;
    std::pair<float, float> m_pos;
    sf::Thread          *m_thread;
    Ball                *m_ball;
};

#endif // PLAYER_HPP
