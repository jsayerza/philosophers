/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_is_dead(t_philo *philo)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= philo->time_to_die)
		is_dead = true;
	pthread_mutex_unlock(philo->meal_lock);
	return (is_dead);
}

static int	check_any_dead(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		if (check_philo_is_dead(&prog->philos[i]))
		{
			print_msg("is dead!!! 💀 ", &prog->philos[i]);
			pthread_mutex_lock(prog->philos[i].dead_lock);
			*prog->philos[i].dead = true;
			pthread_mutex_unlock(prog->philos[i].dead_lock);
			return (true);
		}
		i++;
	}
	return (false);
}

static int	check_all_ate(t_prog *prog)
{
	int	i;
	int	philos_ate_count;

	philos_ate_count = 0;
	i = 0;
	while (i < prog->num_philos)
	{
		pthread_mutex_lock(prog->philos[i].meal_lock);
		if (prog->philos[i].meals_eaten >= prog->num_eats)
			philos_ate_count++;
		pthread_mutex_unlock(prog->philos[i].meal_lock);
		i++;
	}
	if (philos_ate_count == prog->num_philos)
	{
		pthread_mutex_lock(prog->philos[0].dead_lock);
		*prog->philos[0].dead = true;
		pthread_mutex_unlock(prog->philos[0].dead_lock);
		return (true);
	}
	return (false);
}

void	*check(void *ptr)
{
	t_prog	*prog;

	prog = (t_prog *)ptr;
	while (1)
		if (check_any_dead(prog) == true || check_all_ate(prog) == true)
			break ;
	return (ptr);
}
