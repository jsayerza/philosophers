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

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

# define RESET    "\033[0m"
# define RED      "\033[31m"
# define GREEN    "\033[32m"

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				num_philos;
	int				num_eats;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			last_meal;
	size_t			start_time;
	int				meals_eaten;
	int				*dead;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_prog
{
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_eats;
	int				dead_flag;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
}					t_prog;

//philo.c

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
int		thread_create(t_prog *prog);

//control.c
void	*control(void *ptr);

//destroy.c
void	forks_destroy_and_free(t_prog *prog);
void	destroy_and_free(t_prog *prog, char *msg, bool exit_failure);

//print.c
void	print_msg(char *s, t_philo *philo);
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
