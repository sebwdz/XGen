#ifndef WINDOW_HPP
#define WINDOW_HPP

#include        <SFML/Graphics.hpp>
#include        "include/Map.hpp"
#include        "include/Snake.hpp"

class Window
{
public:
    Window();

    bool                isOpen() const;
    void                set_view(Snake &);
    void                show_map(Map &);
    void                show_snake(Snake const&);
    bool                get_real();

private:
    sf::RenderWindow    m_win;
    sf::View            m_view;
    bool                m_real;
};

#endif // WINDOW_HPP
