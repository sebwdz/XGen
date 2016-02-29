#ifndef BOARD_HPP
#define BOARD_HPP

# include                <SFML/Graphics.hpp>
# include               "Ball.hpp"
# include               "Player.hpp"

class                   Board
{
public:
    Board();
    ~Board();

    void                setPlayer(Player*, int);
    void                check_colision();
    void                play();
    void                change_dir(std::pair<float, float> const &);
    void                display_board(sf::RenderWindow &window);
    void                display_ball(sf::RenderWindow &);
    void                display_player(Player *player, sf::RenderWindow &window);

private:
    Player              *m_player1;
    Player              *m_player2;
    std::pair<unsigned int,
        unsigned int>   m_score;
    Ball                m_ball;
    sf::Font            m_font;
    sf::Text            m_text;
    sf::RenderWindow    *m_window;
    sf::View            m_view;
    sf::Clock           m_clock;
};

#endif // BOARD_HPP
