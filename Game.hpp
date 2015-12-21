#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <cmath>
# include <map>
# include <SFML/Graphics.hpp>

# define WINX 800
# define WINY 800

# define BORDER 20
# define LINE 5

class Game {
	public:
		Game();
		Game(std::ifstream &fs);
		~Game();

		void		display();
		int			gameOn();
	private:
		char							board[12][12];
		int								cell;
		sf::RenderWindow				*win;
		sf::RectangleShape				taiyo;
		sf::RectangleShape				ryu;
		sf::RectangleShape				katana;
		sf::RectangleShape				sagi;
		sf::RectangleShape				center;
		sf::CircleShape					pl1;
		sf::CircleShape					pl2;
		sf::Texture						Tryu;
		sf::Texture						Ttaiyo;
		sf::Texture						Tkatana;
		sf::Texture						Tsagi;
		sf::Texture						Tcenter;
		sf::RectangleShape				shiro1;
		sf::RectangleShape				shiro2;
		sf::RectangleShape				outline;
		std::pair<int,int>				select;
		int								player;
		int								number;
		std::vector<std::pair<int,int>>	p1;
		std::vector<std::pair<int,int>>	p2;
		std::map<sf::Keyboard::Key, int>    keymap;

		void		printPlayer(sf::CircleShape &, std::pair<int,int>);
		void		isValidTarget(bool);
		void		printGrid();
		void		printOutline(int, int);
		void		printCell(sf::RectangleShape &, int, int);
		void		printShiro(int, int);
};

#endif
