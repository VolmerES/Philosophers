NAME = philo
CC = gcc
SRC = ./parsing.c ./philo.c ./error.c ./init.c ./safe.c

#SRC_BONUS = 

OBJS = $(SRC:.c=.o)
CFLAGS = #-Wall -Wextra -Werror -g3
#OBJS_BONUS = $(SRC_BONUS:.c=.o )
FT_LIB = ./libft/libft.a

all : $(NAME)
	@echo "\x1b[32m Compilacion PHILO: OK"

$(NAME) : $(OBJS) $(FT_LIB)
	@$(CC) $(OBJS) -o $(NAME) -Llibft -lft 

$(FT_LIB) : 
	@make -C ./libft/

%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@

#BONUS : $(OBJS_BONUS) $(OBJS)
#	@$(CC) $(NAME) $?

clean:
	@rm -f $(OBJS)
	@make -C ./libft/ clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft/ fclean

re: fclean all

bonus: BONUS

.PHONY : clean fclean bonus
