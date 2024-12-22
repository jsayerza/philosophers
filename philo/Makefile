CC				=	cc
FLAGS			=	-g -Wextra -Werror -Wall #--sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME			=	philo
PROG_SRC		=	philo.c parse.c init.c threads.c control.c routines.c destroy.c
PROG_OBJ		=	$(PROG_SRC:.c=.o)

NAME_BONUS		=	philo_bonus
PROG_SRC_BONUS	=	#philo_bonus.c
PROG_OBJ_BONUS	=	$(PROG_SRC_BONUS:.c=.o)

UTILS_SRC       =	utils.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

HEADERS			=	philo.h
HEADERS_BONUS	=	#philo_bonus.h
HEADERS_UTILS	=	

#(1)number_of_philosophers (2)time_to_die (3)time_to_eat (4)time_to_sleep (5)[number_of_times_each_philosopher_must_eat]
#				= 1 2   3   4   5
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

# printf("num_philos: %d\n", prog.num_philos);
# printf("time_to_die: %d\n", prog.time_to_die);
# printf("time_to_eat: %d\n", prog.time_to_eat);
# printf("time_to_sleep: %d\n", prog.time_to_sleep);
# printf("num_eats: %d\n", prog.num_eats);
# printf("Number of CPUs available: %d\n", get_num_cpus());
