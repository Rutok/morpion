NAME = morpion

FLG = -Wall -Wextra -Werror

SRC = srcs/main.c \
	  srcs/app.c \
	  srcs/shapes.c

OBJ = $(SRC:%.c=%.o)

INC = -I./includes \
	  -I./engine/libft/includes \
	  -I./engine/includes \
	  -I/usr/include \

LIB = -L./engine/libft \
	  -L./engine \

all: $(NAME)

$(NAME):
	make -C engine 
	gcc $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -lSDL2 -o $(NAME) -O3

debug:
	make -C engine 
	gcc $(FLG) $(LIB) $(INC) $(SRC) -lm -lengine -lft -lSDL2 -o $(NAME) -O3 -g

rex: re
	./$(NAME)

clean:
	make -C engine clean
	rm -f $(NAME)

fclean: clean
	make -C engine fclean
	rm -rf $(OBJ)

re: clean all
