INC = philo.h

NAME = philo

SRC =	parser.c \
		utils.c \
		actions.c \
        libft_utils.c \
        main.c \
        philo_init.c \
        start_simulation.c \

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(INC)
	$(CC) -I $(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -I $(INC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(OBJ) $(NAME)

re: fclean all
