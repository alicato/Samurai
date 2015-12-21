#include "Game.hpp"

int main(int ac, char **av) {
	std::ifstream	fs;

	fs.open("board.map");
	if (fs.is_open()) {
		Game	game(fs);
		fs.close();
		while (game.gameOn())
			game.display();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
