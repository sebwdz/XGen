#include        "include/Window.hpp"

Window::Window() : m_win(sf::VideoMode(500, 500), "SFML window")
{
    m_view.setSize(500, 500);
    m_real = false;
}

bool                Window::isOpen() const
{
    return (m_win.isOpen());
}

void                Window::set_view(Snake &snake)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        m_real = true;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        m_real = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        snake.setMove(2);
        if (!m_real)
            snake.changeDir(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        snake.setMove(1);
        if (!m_real)
            snake.changeDir(true);
    }
    else
        snake.setMove(0);
    m_view.setCenter(snake.getPos().first * 10, snake.getPos().second * 10);
    m_view.setRotation(snake.getAngle() + 90);
    m_win.setView(m_view);
}

void                Window::show_map(Map &map)
{
    std::pair<int, int> const   &size = map.getSize();
    Map::CaseType                   v;
    sf::RectangleShape          rct;

    m_win.clear();
    rct.setSize(sf::Vector2f(10, 10));
    rct.setOrigin(5, 5);
    for (int x = 0; x < size.first; x++)
    {
        for (int y = 0; y < size.second; y++)
        {
            if (map.getCase(std::make_pair(x, y))._view)
            {
                v = map.getCase(std::make_pair(x, y))._type;
                if (v == Map::EMPTY)
                    rct.setFillColor(sf::Color(50, 50, 50));
                else if (v == Map::WALL)
                    rct.setFillColor(sf::Color(0, 0, 255));
                else
                    rct.setFillColor(sf::Color(255, 0, 0));
                rct.setPosition(x * 10, y * 10);
                m_win.draw(rct);
            }
            map.getCase(std::make_pair(x, y))._view = false;
        }
    }
}
void                Window::show_snake(Snake const& snake)
{
    sf::RectangleShape          rct;

    rct.setSize(sf::Vector2f(10, 10));
    rct.setFillColor(sf::Color(0, 255, 0));
    rct.rotate(snake.getAngle());
    rct.setPosition(snake.getPos().first * 10, snake.getPos().second * 10);
    rct.setOrigin(5, 5);
    m_win.draw(rct);
    m_win.display();
}

bool                Window::get_real()
{
    return (m_real);
}
