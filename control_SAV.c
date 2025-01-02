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

// static int	check_philo_is_dead(t_philo *philo)
// {
// 	bool	is_dead;

// 	is_dead = false;
// 	pthread_mutex_lock(philo->meal_lock);
// 	if (get_current_time() - philo->last_meal >= philo->time_to_die)
// 		is_dead = true;
// 	pthread_mutex_unlock(philo->meal_lock);
// 	return (is_dead);
// }

// static int	check_any_dead(t_prog *prog)
// {
// 	int	i;

// 	i = 0;
// 	while (i < prog->num_philos)
// 	{
// 		if (check_philo_is_dead(&prog->philos[i]))
// 		{
// 			print_msg("died!!! 💀 ", &prog->philos[i]);
// 			pthread_mutex_lock(prog->philos[i].dead_lock);
// 			*prog->philos[i].dead = true;
// 			pthread_mutex_unlock(prog->philos[i].dead_lock);
// 			return (true);
// 		}
// 		i++;
// 	}
// 	return (false);
// }

static int	check_any_dead(t_prog *prog)
{
	int	i;
	size_t	cur_time;
	size_t	elapsed;
	size_t	elapsed_last_meal;

	i = 0;
	while (i < prog->num_philos)
	{
		pthread_mutex_lock(prog->philos[i].meal_lock);
		cur_time = get_current_time();
		elapsed_last_meal = cur_time - prog->philos[i].last_meal;
		if ((elapsed_last_meal > prog->time_to_die) && !prog->philos[i].eating)
		{
			elapsed = cur_time - prog->philos[i].start_time;
			printf("%zu [%zu] CheckTime Philo(%d) LastMeal: %zu Elap_last_m: %zu Eating:%d\n", \
			cur_time, elapsed, prog->philos[i].philo_id, \
			prog->philos[i].last_meal, elapsed_last_meal, prog->philos[i].eating);
			pthread_mutex_unlock(prog->philos[i].meal_lock);

			print_msg("died!!! 💀 ", &prog->philos[i]);
			pthread_mutex_lock(prog->philos[i].dead_lock);
			*prog->philos[i].dead = true;
			pthread_mutex_unlock(prog->philos[i].dead_lock);
			return (true);
		}
		pthread_mutex_unlock(prog->philos[i].meal_lock);
		i++;
	}
	return (false);
}

static bool	check_all_ate(t_prog *prog)
{
	int	i;
	int	philos_ate_count;

	if (prog->num_eats > 0)
	{
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
	}	
	return (false);
}

void	*control(void *ptr)
{
//	t_prog	*prog;
	t_philo	*philos;

//	prog = (t_prog *)ptr;
	philos = (t_philo *)ptr;
	while (true)
		if (check_any_dead(philos) == true || check_all_ate(philos) == true)
			return (NULL);
	return (NULL);
}
