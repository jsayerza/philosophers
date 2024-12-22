/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_msg("is sleeping 💤 ", philo);
	ft_usleep(philo->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_msg("is thinking 💭 ", philo);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_right);
	print_msg("toke right fork", philo);
	pthread_mutex_lock(philo->fork_left);
	print_msg("toke left fork", philo);
	philo->eating = true;
	print_msg("is eating 🍜 ", philo);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = false;
	print_msg("ate", philo);
	pthread_mutex_unlock(philo->fork_right);
	print_msg("left right fork", philo);
	pthread_mutex_unlock(philo->fork_left);
	print_msg("left left fork", philo);
}
