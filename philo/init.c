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
		prog->philos[i].thread = 0;
		prog->philos[i].philo_id = i + 1;
		prog->philos[i].eating = false;
		prog->philos[i].meals_eaten = 0;
		prog->philos[i].dead = false;
		prog->philos[i].last_meal = get_current_time();
		prog->philos[i].fork_left = &prog->forks[i];
		if (i == prog->num_philos - 1)
			prog->philos[i].fork_right = &prog->forks[0];
		else
			prog->philos[i].fork_right = &prog->forks[i];
		prog->philos[i].time_to_die = prog->time_to_die;
		prog->philos[i].time_to_eat = prog->time_to_eat;
		prog->philos[i].time_to_sleep = prog->time_to_sleep;
		prog->philos[i].dead_lock = &prog->dead_lock;
		i++;
	}
	print_philos(prog);
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
	pthread_mutex_init(&prog->dead_lock, NULL);
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
}