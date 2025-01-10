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

static bool	check_all_ate(t_philo *philos)
{
	int	i;
	int	philos_ate_count;

	if (philos[0].num_eats == 0)
		return (false);
	philos_ate_count = 0;
	i = 0;
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_eats)
			philos_ate_count++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (philos_ate_count == philos[0].num_philos)
		return (true);
	return (false);
}

static void	set_exit_flag(t_prog *prog)
{
	pthread_mutex_lock(&prog->dead_lock);
	prog->dead_flag = 1;
	pthread_mutex_unlock(&prog->dead_lock);
}

static void	set_dead(t_prog *prog, int i)
{
	pthread_mutex_unlock(prog->philos[i].meal_lock);
	print_msg(RED"died!!! 💀 "RESET, &prog->philos[i]);
	set_exit_flag(prog);
}

void	*control(void *ptr)
{
	t_prog	*prog;
	int		i;

	prog = (t_prog *)ptr;
	while (true)
	{
		i = -1;
		while (++i < prog->philos[0].num_philos)
		{
			pthread_mutex_lock(prog->philos[i].meal_lock);
			if (get_current_time() - prog->philos[i].last_meal
				> prog->philos[i].time_to_die
				&& get_current_time() > prog->philos[i].last_meal)
			{
				set_dead(prog, i);
				return (NULL);
			}
			pthread_mutex_unlock(prog->philos[i].meal_lock);
		}
		if (check_all_ate(prog->philos) == true)
			break ;
	}
	set_exit_flag(prog);
	return (NULL);
}
