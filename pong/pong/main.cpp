
#include                <ctime>
#include                <cstdlib>
#include                "include/Board.hpp"
#include                <X11/Xlib.h>

int                     main(int ac, char **av)
{
    Board               board;
    Player              *player1;
    Player              *player2;

    XInitThreads();
    srand(time(NULL));
    if (ac < 4)
    {
        std::cout << "./pong [ type player1 ] player2" << std::endl;
        return (1);
    }
    if (std::string(av[1]) == "IA")
        player1 = Player::get_player(Player::IA, av[2]);
    else
        player1 = Player::get_player(Player::PLAYER, av[2]);
    player2 = Player::get_player(Player::IA, av[3]);
    board.setPlayer(player1, 1);
    board.setPlayer(player2, 2);
    player2->start();
    if (player1->get_type() == Player::IA)
        player1->start();
    sf::Thread *t = new sf::Thread(&Board::play, &board);
    t->launch();
    t->wait();
    return (0);
}
