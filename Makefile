##
## EPITECH PROJECT, 2023
## Rush_3
## File description:
## Makefile
##

INC_DIR	=	include/

CFLAGS	=	-W -Wall -Wextra -g -Wno-deprecated-declarations -lncurses -I$(INC_DIR)

CPPFLAGS	=	-I/opt/homebrew/Cellar/sfml/2.5.1_1/include/
LDLFLAGS	=	-L//opt/homebrew/Cellar/sfml/2.5.1_1/lib/ -lsfml-window -lsfml-graphics -lsfml-network -lsfml-system -lsfml-audio -lm

SRC	=	$(wildcard *.cpp)

OBJ	=	$(SRC:.cpp=.o)

NAME	=	MyGKrellm

all:	$(NAME)

$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ) $(LDLFLAGS) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
