CC				=	cc
FLAGS			=	-g -Wextra -Werror -Wall --sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME			=	philo
PROG_SRC		=	philo.c parse.c init.c threads.c check.c routines.c destroy.c
PROG_OBJ		=	$(PROG_SRC:.c=.o)

NAME_BONUS		=	philo_bonus
PROG_SRC_BONUS	=	#philo_bonus.c
PROG_OBJ_BONUS	=	$(PROG_SRC_BONUS:.c=.o)

UTILS_SRC       =	utils.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

HEADERS			=	philo.h
HEADERS_BONUS	=	#philo_bonus.h
HEADERS_UTILS	=	

PARAMS			= 5 800 200 200 7

all: 	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME):	$(PROG_OBJ) $(UTILS_OBJ) $(HEADERS) $(HEADERS_UTILS)
	$(CC) $(FLAGS) $(PROG_OBJ) $(UTILS_OBJ) -o $(NAME)
	
$(NAME_BONUS):	$(PROG_OBJ_BONUS) $(UTILS_OBJ) $(HEADERS_BONUS) $(HEADERS_UTILS)
	$(CC) $(FLAGS) $(PROG_OBJ_BONUS) $(UTILS_OBJ) -o $(NAME_BONUS)
	
%.o: %.c Makefile $(HEADERS) $(HEADERS_BONUS) $(HEADERS_UTILS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(PROG_OBJ) $(CLIENT_OBJ) $(UTILS_OBJ) $(PROG_OBJ_BONUS) $(CLIENT_OBJ_BONUS)

fclean:	clean
	$(RM) $(NAME) $(NAME_CLIENT) $(NAME_BONUS) $(NAME_CLIENT_BONUS)

re:		fclean all

run: $(NAME)
	./$(NAME) $(PARAMS)

valgrind: $(NAME)
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(PARAMS)


.PHONY:	all clean fclean re bonus


#valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./server
#valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./client