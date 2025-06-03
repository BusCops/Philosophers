NAME = philo

SRC = main.c args_checker.c helper_function.c utils.c initialize_everything.c philo_work.c monitor.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf 

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

.SECONDARY: $(OBJ)