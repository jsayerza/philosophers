CC				=	cc
FLAGS			=	-g -Wextra -Werror -Wall -lpthread -lrt #--sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME			=	philo_bonus
PROG_SRC		=	philo_bonus.c init_bonus.c destroy_bonus.c control_bonus.c \
					parse_bonus.c 
#threads.c routines.c print.c
PROG_OBJ		=	$(PROG_SRC:.c=.o)

UTILS_SRC       =	../philo/utils.c ../philo/utils_sys.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

HEADERS			=	philo_bonus.h
HEADERS_UTILS	=	

#(1)number_of_philosophers (2)time_to_die (3)time_to_eat (4)time_to_sleep (5)[number_of_times_each_philosopher_must_eat]
#				= 1 2   3   4   5
PARAMS			= 5 800 200 200 7

all: 	$(NAME)

$(NAME):	$(PROG_OBJ) $(UTILS_OBJ) $(HEADERS) $(HEADERS_UTILS)
	$(CC) $(FLAGS) $(PROG_OBJ) $(UTILS_OBJ) -o $(NAME)

%.o: %.c Makefile $(HEADERS) $(HEADERS_UTILS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(PROG_OBJ) $(UTILS_OBJ)

fclean:	clean
	$(RM) $(NAME)

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

# source ~/norminette_env/bin/activate

# inter-process communication (IPC) 