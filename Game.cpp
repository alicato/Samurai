#include "Game.hpp"

Game::Game() {
	throw 0;
}

Game::Game(std::ifstream &fs) {
	win = new sf::RenderWindow(sf::VideoMode(WINX, WINY), "Samurai", sf::Style::Close);
	std::string		line;
	int j = 0;
	while (getline(fs, line)) {
		int i = 0;
		for (char& c : line) {
			board[j][i++] = c;
		}
		board[j][i] = 0;
		j++;
	}
	cell = (WINY - BORDER) / 11;

	pl1.setRadius(cell * 0.4);
	pl1.setFillColor(sf::Color(255, 255, 255, 128));

	pl2.setRadius(cell * 0.4);
	pl2.setFillColor(sf::Color(0, 255, 0, 128));

	taiyo.setSize(sf::Vector2f(cell * .8, cell * .8));
	if (!Ttaiyo.loadFromFile("img/taiyo.png"))
		throw 1;
	Ttaiyo.setSmooth(true);
	taiyo.setTexture(&Ttaiyo);

	ryu.setSize(sf::Vector2f(cell * .8, cell * .8));
	if (!Tryu.loadFromFile("img/ryu.png"))
		throw 1;
	Tryu.setSmooth(true);
	ryu.setTexture(&Tryu);

	katana.setSize(sf::Vector2f(cell * .8, cell * .8));
	if (!Tkatana.loadFromFile("img/katana.png"))
		throw 1;
	Tkatana.setSmooth(true);
	katana.setTexture(&Tkatana);

	sagi.setSize(sf::Vector2f(cell * .8, cell * .8));
	if (!Tsagi.loadFromFile("img/sagi.png"))
		throw 1;
	Tsagi.setSmooth(true);
	sagi.setTexture(&Tsagi);

	center.setSize(sf::Vector2f(cell * .8, cell * .8));
	if (!Tcenter.loadFromFile("img/center.png"))
		throw 1;
	Tcenter.setSmooth(true);
	center.setTexture(&Tcenter);

	shiro1.setSize(sf::Vector2f(sqrt(pow(cell *.79, 2) + pow(cell*.79, 2)), -5));
	shiro1.setFillColor(sf::Color::Black);
	shiro1.rotate(45);
	shiro2.setSize(sf::Vector2f(sqrt(pow(cell *.79, 2) + pow(cell*.79, 2)), 5));
	shiro2.setFillColor(sf::Color::Black);
	shiro2.rotate(-45);

	outline.setSize(sf::Vector2f(cell * .85, cell * .85));
	outline.setOutlineColor(sf::Color::Black);
	outline.setOutlineThickness(cell * .05);
	outline.setFillColor(sf::Color(180, 20, 20));

	keymap[sf::Keyboard::Escape] = 0;
	select.first = -1;

	p1.push_back(std::pair<int,int>(3,0));
	p1.push_back(std::pair<int,int>(4,0));
	p1.push_back(std::pair<int,int>(6,0));
	p1.push_back(std::pair<int,int>(7,0));
	p2.push_back(std::pair<int,int>(3,10));
	p2.push_back(std::pair<int,int>(4,10));
	p2.push_back(std::pair<int,int>(6,10));
	p2.push_back(std::pair<int,int>(7,10));
}

Game::~Game() {
	win->close();
	delete win;
}

int		Game::gameOn() {
	sf::Event event;

	if (win->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return 0;
		else if (event.type == sf::Event::KeyPressed) {
			if (keymap.find(event.key.code) != keymap.end())
				return keymap[event.key.code];
		} else if (event.type == sf::Event::MouseButtonPressed) {
			if (select.first == -1)
				isValidTarget(true);
		} else if (event.type == sf::Event::MouseButtonReleased) {
			if (select.first != -1)
				isValidTarget(false);
			select.first = -1;
		}
	}
	return 1;
}

void	Game::isValidTarget(bool first) {
	sf::Vector2i		position = sf::Mouse::getPosition(*win);
	int i = (position.x - BORDER * 3 / 4) / cell;
	int j = (position.y - BORDER * 3 / 4) / cell;
	std::pair<int,int> c;
	c.first = i;
	c.second = j;
	if (first) {
		auto ret1 = std::find(p1.begin(), p1.end(), c);
		auto ret2 = std::find(p2.begin(), p2.end(), c);
		if (ret1 != p1.end()) {
			player = 1;
			number = ret1 - p1.begin();
			select.first = i;
			select.second = j;
		} else if (ret2 != p2.end()) {
			player = 2;
			number = ret2 - p2.begin();
			select.first = i;
			select.second = j;
		}
	} else if (std::find(p1.begin(), p1.end(), c) == p1.end() && std::find(p2.begin(), p2.end(), c) == p2.end()) {
		if (player == 1) {
			p1[number].first = i;
			p1[number].second = j;
		} else if (player == 2) {
			p2[number].first = i;
			p2[number].second = j;
		}
		select.first = -1;
	}
}

void	Game::display() {
	win->clear(sf::Color(166, 128, 100));
	printGrid();
	win->display();
}

void	Game::printGrid() {
	sf::RectangleShape	border(sf::Vector2f(WINX - BORDER * 2 + LINE * 2, WINY - BORDER * 2 + LINE * 2));
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(LINE);
	border.setPosition(BORDER - LINE, BORDER - LINE);
	border.setFillColor(sf::Color(180, 20, 20));
	win->draw(border);

	for (int j = 0; j < 11; j++) {
		for (int i = 0; i < 11; i++) {
			printOutline(i, j);
			if (board[j][i] == 'o')
				printCell(taiyo, i, j);
			else if (board[j][i] == 'l')
				printCell(katana, i, j);
			else if (board[j][i] == 'w')
				printCell(ryu, i, j);
			else if (board[j][i] == 'v')
				printCell(sagi, i, j);
			else if (board[j][i] == 'X')
				printShiro(i, j);
			else if (board[j][i] == '0')
				printCell(center, i, j);
		}
	}
	for (int i = 0; i <= 3; i++) {
		printPlayer(pl1, p1[i]);
		printPlayer(pl2, p2[i]);
	}
}

void	Game::printPlayer(sf::CircleShape &p, std::pair<int,int> c) {
	p.setPosition(BORDER + cell * c.first + 1, BORDER + cell * c.second + 1);
	win->draw(p);
}

void	Game::printOutline(int i, int j) {
	sf::Vector2i		position = sf::Mouse::getPosition(*win);
	int x = (position.x - 3 * BORDER / 4) / cell;
	int y = (position.y - 3 * BORDER / 4) / cell;
	if (x == i && y == j)
		outline.setFillColor(sf::Color(220, 50, 50));
	if (i == select.first && j == select.second)
	{
		outline.setFillColor(sf::Color(150, 15, 15));
		outline.setOutlineColor(sf::Color::Green);
	}
	outline.setPosition(BORDER + cell * i, BORDER + cell * j);
	win->draw(outline);
	outline.setFillColor(sf::Color(180, 20, 20));
	outline.setOutlineColor(sf::Color::Black);
}

void	Game::printCell(sf::RectangleShape &rect, int i, int j) {
	rect.setPosition(BORDER + cell * i, BORDER + cell * j);
	win->draw(rect);
}

void	Game::printShiro(int i, int j) {
	shiro1.setPosition(BORDER + cell * i, BORDER + cell * j + cell *.05);
	shiro2.setPosition(BORDER + cell * i, BORDER + cell * j + cell *.8);
	win->draw(shiro1);
	win->draw(shiro2);
}
