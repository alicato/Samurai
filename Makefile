NAME=samurai

all: $(NAME)

$(NAME): main.cpp Game.cpp
	@c++ -Wall -Werror -std=c++11 main.cpp Game.cpp -o $(NAME) -I ~/.brew/include -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,$(HOME)/.brew/lib

clean:
	@/bin/rm -f $(NAME)

fclean: clean

re: clean all
