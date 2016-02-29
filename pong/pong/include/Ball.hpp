#ifndef BALL_HPP
#define BALL_HPP

# include           <iostream>
# include           "Player.hpp"

class               Ball
{
public:
    Ball();
    ~Ball();

    std::pair<float, float> &get_pos();
    void                    move();
    void                    reset();
    void                    change_dir(std::pair<float, float> const &vct);
    bool                    check_colision(Player*);
    void                    rotate(float dir);
private:
    std::pair<float, float> m_pos;
    std::pair<float, float> m_dir;
    float                   m_velocity;
};

#endif // BALL_HPP
