/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:30 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/wait.h>

# define DIE_SEM_NAME "/die_sem"
# define FORK_SEM_NAME "/fork_sem"
# define MEAL_SEM_NAME "/meal_sem"
# define WRITE_SEM_NAME "/write_sem"

# define RESET    "\033[0m"
# define RED      "\033[31m"
# define GREEN    "\033[32m"

typedef struct s_sems
{
	sem_t	*fork_sem;
	sem_t	*die_sem;
	sem_t	*meal_sem;
	sem_t	*print_sem;
}	t_sems;

typedef struct s_philo
{
	int		philo_id;
	int		num_philos;
	int		num_eats;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	start_time;
	size_t	last_meal;
	int		eating;
	int		meals_eaten;
	int		*dead;
	t_sems	*sems;
}			t_philo;

typedef struct s_prog
{
	int		num_philos;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		num_eats;
	int		exit_flag;
	t_philo	*philos;
	pid_t	*proc_ids;
	t_sems	*sems;
}			t_prog;

//philo_bonus.c

//parse.c
void	parse_param_philos(t_prog *prog, char *s);
void	parse_param_die(t_prog *prog, char *s);
void	parse_param_eat(t_prog *prog, char *s);
void	parse_param_sleep(t_prog *prog, char *s);
void	parse_param_num_eats(t_prog *prog, char *s);

//init.c
void	init_philos(t_prog *prog);
void	init_forks(t_prog *prog);
void	init_prog(t_prog *prog);
void	init(t_prog *prog);

//simulation.c
void	philos_create(t_prog *prog);
void	simulation(t_prog *prog);

//control.c
void	*control_ate(void *ptr);
void	*control_die(void *ptr);

//destroy.c
void	destroy_and_free(t_prog *prog, char *msg, bool isParentProc, \
	bool exit_failure);

//print.c
void	print_msg(int philo_id, size_t start_time, char *s, sem_t *semt);
void	print_philosopher(t_philo *philo);
void	print_philos(t_philo *philos);

//utils.c
long	ft_atoi(char *s);
void	ft_usleep(size_t time_to_sleep);
void	check_is_num(char *s);

//utils_sys.c
size_t	get_current_time(void);
int		get_num_cpus(void);
int		get_current_cpu(void);

#endif