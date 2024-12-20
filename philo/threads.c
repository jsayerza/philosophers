/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_dead(t_philo *philo)
{
	bool is_dead;

	is_dead = false;
	pthread_mutex_lock(philo->dead_lock);
	if (philo->dead == true)
		is_dead = true;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

static void	*philo_loop(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (!philo_is_dead(philo))
	{
		philo_think(philo);
		philo_sleep(philo);
	}
	return	(ptr);
}

void	thread_create(t_prog *prog)
{
	pthread_t	controller;
	int			i;

	if (pthread_create(&controller, NULL, &check, prog->philos) != 0)
		destroy_and_free(prog, "Failed to create controller thread", true);
	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, \
			&philo_loop, &prog->philos[i]) != 0)
			destroy_and_free(prog, "Failed to create philosophers' threads", true);
		i++;
	}
	if (pthread_join(controller, NULL) != 0)
		destroy_and_free(prog, "Failed to join controller thread", true);
	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			destroy_and_free(prog, "Failed to join philosophers' threads", true);
		i++;
	}
}