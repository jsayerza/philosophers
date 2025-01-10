/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:20:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/20 16:02:59 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *s, t_philo *philo)
{
	int	exit_flag;

	pthread_mutex_lock(philo->dead_lock);
	exit_flag = *(philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	if (exit_flag == 0)
	{
		pthread_mutex_lock(philo->print_lock);
		printf("%zu %d %s\n", \
			get_current_time() - philo->start_time, philo->philo_id, s);
		pthread_mutex_unlock(philo->print_lock);
	}
}

void	print_msg_detailed(char *s, t_philo *philo)
{
	size_t	cur_time;
	size_t	elapsed;
	size_t	elapsed_last_meal;

	pthread_mutex_lock(philo->print_lock);
	cur_time = get_current_time();
	elapsed = cur_time - philo->start_time;
	elapsed_last_meal = cur_time - philo->last_meal;
	get_current_cpu();
	if (s[0] == 'a')
		printf("%zu [%zu] %d %s --> %d\n", \
			cur_time, elapsed, philo->philo_id, s, philo->meals_eaten);
	else
		printf("%zu [%zu] %d %s elapsed_last_meal:[%zu]\n", \
			cur_time, elapsed, philo->philo_id, s, elapsed_last_meal);
	pthread_mutex_unlock(philo->print_lock);
}

void	print_philosopher(t_philo *philo)
{
	printf("Philo (%d):\n", philo->philo_id);
	printf("  Eaten: %d\n", philo->meals_eaten);
	printf("  #philos: %d #eats: %d\n", \
		philo->num_philos, philo->num_eats);
	printf("  start_time: %zu\n", \
		philo->start_time);
	printf("  last_meal : %zu \n", \
		philo->last_meal);
	printf("  forkL:%p forkR:%p \n", \
		philo->fork_left, philo->fork_right);
	printf("  Exit flag or any dead? %d\n", \
		(int) *philo->dead);
}

void	print_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		print_philosopher(&philos[i]);
		i++;
	}
}
