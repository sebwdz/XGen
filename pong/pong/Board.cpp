
#include                    <sstream>
#include                    "include/Board.hpp"

Board::Board()
{
    m_player1 = NULL;
    m_player2 = NULL;
    m_font.loadFromFile("font.ttf");
    m_text.setFont(m_font);
    m_text.setString("0 | 0");
    m_text.setColor(sf::Color(255, 255, 255));
    m_text.setPosition(-30, -20);
    m_text.setCharacterSize(50);
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Pong");
    m_view.setCenter(0, 0);
    m_view.setSize(800, 600);
    m_window->setView(m_view);
    m_window->setActive(false);
}

Board::~Board()
{

}

void                    Board::setPlayer(Player *player, int nb)
{
    if (nb == 1)
        m_player1 = player;
    else
        m_player2 = player;
}

void                    Board::play()
{
    bool                press[2] = {false, false};

    m_clock.restart();
    m_player1->set_ball(&m_ball);
    m_player2->set_ball(&m_ball);
    m_player1->set_pos(std::make_pair(280, 0));
    m_player2->set_pos(std::make_pair(-280, 0));
    m_ball.reset();
    m_window->setKeyRepeatEnabled(false);
    while (m_window->isOpen())
    {
       sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                m_window->close();
            if (event.type == sf::Event::KeyPressed ||
                    event.type == sf::Event::KeyReleased )
            {
                if (event.key.code == sf::Keyboard::Down)
                    press[1] = !press[1];
                else if (event.key.code == sf::Keyboard::Up)
                    press[0] = !press[0];
            }
        }
        check_colision();
        if (m_player1->get_type() == Player::PLAYER)
        {
            if (press[1])
                m_player1->move(9);
            if (press[0])
                m_player1->move(-9);
        }
        m_ball.move();
        if (m_clock.getElapsedTime().asMilliseconds() > 200)
        {
            m_clock.restart();
            m_player1->show();
            m_player2->show();
        }
        m_window->clear();
        display_ball(*m_window);
        display_player(m_player1, *m_window);
        display_player(m_player2, *m_window);
        display_board(*m_window);
        m_window->draw(m_text);
        m_window->display();
    }
}

void                Board::check_colision()
{
    float                 dir;
    std::stringstream    str;

    if (m_ball.check_colision(m_player1) || m_ball.check_colision(m_player2))
    {
        if (m_ball.get_pos().first > 270)
        {
            m_ball.get_pos().first = 270;
            dir = m_ball.get_pos().second - m_player1->get_pos().second;
            dir *= -1;
        }
        else
        {
            m_ball.get_pos().first = -270;
            dir = m_ball.get_pos().second - m_player2->get_pos().second;
        }
        dir /= 60.0;
        m_ball.change_dir(std::make_pair(1, -1));
        if (dir)
            m_ball.rotate(dir);
    }
    else if (m_ball.get_pos().first >= 280 || m_ball.get_pos().first <= -280)
    {
        if (m_ball.get_pos().first >= 280)
            m_score.first++;
        else
            m_score.second++;
        str << m_score.first << " | " << m_score.second;
        m_text.setString(str.str().c_str());
        m_ball.reset();
    }
    else if (m_ball.get_pos().second >= 245 || m_ball.get_pos().second <= -245)
    {
        if (m_ball.get_pos().second >= 245)
            m_ball.get_pos().second = 245;
        else
            m_ball.get_pos().second = -245;
        m_ball.change_dir(std::make_pair(-1, 1));
    }
}

void                Board::display_board(sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(600, 10));
    rectangle.setOrigin(300, 0);

    rectangle.setPosition(0, 245);
    window.draw(rectangle);
    rectangle.setPosition(0, -245);
    window.draw(rectangle);
}

void                Board::display_ball(sf::RenderWindow &window)
{
    sf::CircleShape shape(10);

    shape.setFillColor(sf::Color(255, 250, 255));
    shape.setPosition(m_ball.get_pos().first, m_ball.get_pos().second);
    shape.setOrigin(5, 5);
    window.draw(shape);
}

void                Board::display_player(Player *player, sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(10, 80));
    rectangle.setOrigin(5, 40);

    rectangle.setPosition(player->get_pos().first, player->get_pos().second);
    rectangle.setFillColor(sf::Color(255, 255, 255));
    window.draw(rectangle);
}
