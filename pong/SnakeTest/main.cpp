
#include            <iostream>
#include            "include/Snake.hpp"
#include            "include/Window.hpp"

int                 main()
{
    Snake           snake;
    Map             map;
    Window          win;

    std::cout << "test ia snake v.0" << std::endl;
    while (win.isOpen())
    {
        usleep(10000);
        win.set_view(snake);
        win.show_map(map);
        win.show_snake(snake);
        snake.exec(map, win.get_real());
    }
    return (0);
}
