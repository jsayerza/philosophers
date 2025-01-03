/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosopher(t_prog *prog, t_philo *philo, int i)
{
	prog->philos[i].thread = 0;
	prog->philos[i].philo_id = i + 1;
	prog->philos[i].num_philos = prog->num_philos;
	prog->philos[i].num_eats = prog->num_eats;
	prog->philos[i].time_to_die = prog->time_to_die;
	prog->philos[i].time_to_eat = prog->time_to_eat;
	prog->philos[i].time_to_sleep = prog->time_to_sleep;
	prog->philos[i].fork_left = &prog->forks[i];
	prog->philos[i].eating = false;
	prog->philos[i].meals_eaten = 0;
	prog->philos[i].dead = &prog->dead_flag;
	prog->philos[i].start_time = get_current_time();
	prog->philos[i].last_meal = prog->philos[i].start_time;
	prog->philos[i].dead_lock = &prog->dead_lock;
	prog->philos[i].meal_lock = &prog->meal_lock;
	prog->philos[i].print_lock = &prog->print_lock;
}

void	init_philos(t_prog *prog)
{
	int	i;

	prog->philos = malloc(sizeof(t_philo) * prog->num_philos);
	if (!prog->philos)
	{
		perror("Failed to allocate memory for philosophers");
		forks_destroy_and_free(prog);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < prog->num_philos)
	{
		init_philosopher(prog, &prog->philos[i], i);
		i++;
	}
	i = 0;
	while (i < prog->num_philos)
	{
		if (i == prog->num_philos - 1)
			prog->philos[i].fork_right = &prog->forks[0];
		else
			prog->philos[i].fork_right = &prog->forks[i + 1];
		i++;
	}
}

void	init_forks(t_prog *prog)
{
	int	i;

	prog->forks = malloc(sizeof(pthread_mutex_t) * prog->num_philos);
	if (!prog->forks)
	{
		perror("Failed to allocate memory for forks mutex");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_mutex_init(&prog->forks[i], NULL) != 0)
		{
			perror("Failed to initialize forks mutex");
			while (--i >= 0)
				pthread_mutex_destroy(&prog->forks[i]);
			free(prog->forks);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	init_prog(t_prog *prog)
{
	if (prog->num_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		ft_usleep(prog->time_to_die);
		printf("%ld 1 died!!! 💀\n", prog->time_to_die);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->print_lock, NULL);
}

void	init(t_prog *prog)
{
	prog->num_philos = 0;
	prog->time_to_die = 0;
	prog->time_to_eat = 0;
	prog->time_to_sleep = 0;
	prog->num_eats = 0;
	prog->philos = NULL;
	prog->forks = NULL;
	prog->dead_flag = 0;
}
