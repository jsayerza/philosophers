CC				=	cc
FLAGS			=	-g -Wextra -Werror -Wall -lpthread #--sanitize=address
RM				=	rm -f
INCLUDES		=	-I.

NAME			=	philo
PROG_SRC		=	philo.c parse.c init.c threads.c control.c destroy.c print.c
PROG_OBJ		=	$(PROG_SRC:.c=.o)

UTILS_SRC       =	utils.c utils_sys.c
UTILS_OBJ       =	$(UTILS_SRC:.c=.o)

HEADERS			=	philo.h
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

valgrind1: $(NAME)
#	For memory leaks and invalid accesses:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(PARAMS)

.PHONY:	all clean fclean re run valgrind1 


# source ~/norminette_env/bin/activate

# x veure detall philos al final colocar a philo.c/main() després de thread_create()
#	print_philos(prog.philos);

# X imprimir init prog detallat colocar a philo.c/main() abans de thread_create()
# printf("num_philos: %d\n", prog.num_philos);
# printf("time_to_die: %d\n", prog.time_to_die);
# printf("time_to_eat: %d\n", prog.time_to_eat);
# printf("time_to_sleep: %d\n", prog.time_to_sleep);
# printf("num_eats: %d\n", prog.num_eats);
# printf("Number of CPUs available: %d\n", get_num_cpus());

# x veure més detall d'accions, colocar això a routines.c/philo_eat(), després de: philo->eating = false;
#	print_msg("ate", philo);
# + renombrar print.c/print_msg_detailed() a print_msg()

# x ctrlar deads a control.c/check_any_dead(), dins l'if
# long int	elapsed;
# 		elapsed = cur_time - philos[i].start_time;
# 		printf("%zu [%zu] CheckTime Philo(%d) LastMeal: %zu Elap_last_m: %zu Eating:%d\n", \
# 		cur_time, elapsed, philos[i].philo_id, \
# 		philos[i].last_meal, elapsed_last_meal, philos[i].eating);




#valgrind2: $(NAME)
#	For thread-related race conditions:
#	valgrind -s --tool=helgrind ./$(NAME) $(PARAMS)
#valgrind3: $(NAME)
#	For detecting possible thread errors like deadlocks:
#	valgrind -s --tool=drd ./$(NAME) $(PARAMS)