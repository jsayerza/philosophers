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

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_msg("toke left fork", philo);
	pthread_mutex_lock(philo->fork_right);
	print_msg("toke right fork", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = true;
	pthread_mutex_unlock(philo->meal_lock);
	print_msg("is eating 🍜 ", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = true;
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	philo->eating = false;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->fork_left);
	print_msg("left left fork", philo);
	pthread_mutex_unlock(philo->fork_right);
	print_msg("left right fork", philo);
}

static void	philo_loop(t_philo	*philo)
{
	philo_eat(philo);
	print_msg("is sleeping 💤 ", philo);
	ft_usleep(philo->time_to_sleep);
	print_msg("is thinking 💭 ", philo);
}

void	*start_philo_loop(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->dead_lock);
	philo->start_time = get_current_time();
	pthread_mutex_unlock(philo->dead_lock);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead != 0)
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);
		philo_loop(philo);
	}
	return (NULL);
}

int	thread_create(t_prog *prog)
{
	pthread_t	controller;
	int			i;

	if (pthread_create(&controller, NULL, &control, prog) != 0)
		destroy_and_free(prog, "Failed to create controller thread", true);
	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_create(&prog->philos[i].thread, NULL, \
			&start_philo_loop, &prog->philos[i]) != 0)
			destroy_and_free(prog, "Failed to create philosophers' threads", \
				true);
		i++;
	}
	if (pthread_join(controller, NULL) != 0)
		destroy_and_free(prog, "Failed to join controller thread", true);
	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_join(prog->philos[i].thread, NULL) != 0)
			destroy_and_free(prog, "Failed to join philos' threads", true);
		i++;
	}
	return (0);
}
