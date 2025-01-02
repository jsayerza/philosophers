/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:00:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/20 15:50:30 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
//# include <sched.h>
//# include <limits.h>
//# include <sys/time.h>
//# include <sys/types.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>

# define DIE_SEM_NAME "/die_sem"
# define FORK_SEM_NAME "/fork_sem"
# define MEAL_SEM_NAME "/meal_sem"
# define WRITE_SEM_NAME "/write_sem"

typedef struct s_sems
{
	sem_t	*die_sem;
	sem_t	*fork_sem;
	sem_t	*meal_sem;
	sem_t	*write_sem;
}	t_sems;

typedef struct s_philo
{
	// pthread_t	thread;
	int			philo_id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	size_t		start_time;
	size_t		last_meal;
	bool		eating;
	int			meals_eaten;
	bool		*dead;
	t_sems		*sems;
	// pthread_mutex_t	*fork_left;
	// pthread_mutex_t	*fork_right;
	// pthread_mutex_t	*dead_lock;
	// pthread_mutex_t	*meal_lock;
	// pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_prog
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_eats;
	bool		dead_flag;
	t_philo		*philos;
	pid_t		*proc_id;
	t_sems		*sems;
	// pthread_mutex_t	*forks;
	// pthread_mutex_t	dead_lock;
	// pthread_mutex_t	meal_lock;
	// pthread_mutex_t	print_lock;
}				t_prog;

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

//threats.c
int		philo_is_dead(t_philo *philo);
int		thread_create(t_prog *prog);

//routines.c
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_think(t_philo *philo);

//control.c
void	*check(void *ptr);

//destroy.c
void	destroy_and_free(t_prog *prog, char *msg, bool isParentProc, \
	bool exit_failure);

//print.c
void	print_msg(char *s, t_philo *philo);
void	print_philos(t_prog *prog);

//utils.c
long	ft_atoi(char *s);
void	ft_usleep(size_t time_to_sleep);
void	check_is_num(char *s);

//utils_sys.c
size_t	get_current_time(void);
int		get_num_cpus(void);
int		get_current_cpu(void);

#endif
