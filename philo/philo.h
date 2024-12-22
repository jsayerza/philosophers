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

# define _GNU_SOURCE

# include <sched.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	size_t			last_meal;
	size_t			start_time;
	bool			eating;
	int				meals_eaten;
	bool			*dead;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_prog
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eats;
	bool			dead_flag;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
}					t_prog;

//main.c
size_t	get_current_time(void);
int		get_num_cpus(void);
int		get_current_cpu(void);

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
void	forks_destroy_and_free(t_prog *prog);
void	destroy_and_free(t_prog *prog, char *msg, bool exit_failure);

//utils.c
void	print_msg(char *s, t_philo *philo);
void	print_philos(t_prog *prog);
long	ft_atoi(char *s);
void	ft_usleep(size_t time_to_sleep);
void	check_is_num(char *s);

#endif
