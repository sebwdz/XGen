
#include                    <ctime>
#include                    <cstdlib>
#include                    <cmath>
#include                    "include/Ball.hpp"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void                    Ball::reset()
{
    float       length;

    m_pos.first = 0;
    m_pos.second = 0;
    m_dir.first = (rand() % 100) - 50;
    m_dir.second = (rand() % 100) - 50;
    m_dir.first *= 2;
    length = sqrt(m_dir.first * m_dir.first + m_dir.second * m_dir.second);
    m_dir.first /= length;
    m_dir.second /= length;
    m_velocity = 5;
}

bool                    Ball::check_colision(Player *player)
{
    if (((m_pos.first >= 270 && player->get_pos().first > 0) ||
            (m_pos.first <= -270 && player->get_pos().first < 0)) &&
            m_pos.second <= player->get_pos().second + 55 &&
            m_pos.second >= player->get_pos().second - 55)
        return (true);
    return (false);
}

std::pair<float, float> &Ball::get_pos()
{
    return (m_pos);
}

void                    Ball::move()
{
    m_pos.first += m_dir.first * m_velocity;
    m_pos.second += m_dir.second * m_velocity;
    m_velocity += 0.001 * m_velocity;
    if (m_velocity > 30)
        m_velocity = 30;
}

void                Ball::rotate(float dir)
{
    m_dir.first = m_dir.first * cos(dir) + m_dir.second * -sin(dir);
    m_dir.second = m_dir.second * cos(dir) + m_dir.first * sin(dir);
}

void                Ball::change_dir(std::pair<float, float> const &vct)
{
    std::pair<float, float> tmp;
    float           length;

    m_dir.second *= vct.first;
    m_dir.first *= vct.second * (1 + (rand() % 100) / 100.0);
    length = sqrt(m_dir.first * m_dir.first + m_dir.second * m_dir.second);
    m_dir.first /= length;
    m_dir.second /= length;
    if (m_dir.first < 0.01 && m_dir.first > -0.1)
        m_dir.first = 0.01;
}
