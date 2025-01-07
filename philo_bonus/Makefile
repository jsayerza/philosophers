CC				=	cc
FLAGS			=	-g -Wextra -Werror -Wall -lpthread -lrt #--sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME			=	philo_bonus
PROG_SRC		=	philo_bonus.c init_bonus.c simulation_bonus.c print_bonus.c destroy_bonus.c\
					../philo/parse.c 
PROG_OBJ		=	$(PROG_SRC:.c=.o)

UTILS_SRC       =	../philo/utils.c ../philo/utils_sys.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

HEADERS			=	philo_bonus.h
HEADERS_UTILS	=	

#(1)number_of_philosophers (2)time_to_die (3)time_to_eat (4)time_to_sleep (5)[number_of_times_each_philosopher_must_eat]
#				= 1 2   3   4   5
PARAMS			= 200 800 200 200 7

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

valgrind1: $(NAME)
#	For memory leaks and invalid accesses:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(PARAMS)


.PHONY:	all clean fclean re run valgrind1

# source ~/norminette_env/bin/activate

# x veure detall d'ates, colocar això a simulation_bonus.c/philo_eat(), després de: philo->meals_eaten++;
# snprintf(message, sizeof(message), GREEN"ate --> %d"RESET, philo->meals_eaten);
# print_msg(philo->philo_id, philo->start_time, message, prog_sems->print_sem);





#valgrind2: $(NAME)
#	For thread-related race conditions:
#	valgrind -s --tool=helgrind ./$(NAME) $(PARAMS)
#valgrind3: $(NAME)
#	For detecting possible thread errors like deadlocks:
#	valgrind -s --tool=drd ./$(NAME) $(PARAMS)