/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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
	size_t	elapsed;
	size_t	elapsed_last_meal;

	pthread_mutex_lock(philo->print_lock);
	get_current_cpu();
	elapsed = get_current_time() - philo->start_time;
	elapsed_last_meal = get_current_time() - philo->last_meal;
	if (!philo_is_dead(philo))
	{
		if (s[0] == 'a')
			printf("[%zu] %d %s --> %d\n", elapsed, philo->philo_id, s, \
				philo->meals_eaten);
		else
			printf("[%zu] %d %s [%zu] \n", elapsed, philo->philo_id, s, \
				elapsed_last_meal);
	}
	pthread_mutex_unlock(philo->print_lock);
}

void	print_philos(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		printf("Philo (%d):\n", prog->philos[i].philo_id);
		printf("  Eating: %d  Eaten: %d Time-eat: %d last_meal: %ld\n", \
		prog->philos[i].eating, \
		prog->philos[i].meals_eaten, prog->philos[i].time_to_eat, \
		get_current_time() - prog->philos[i].last_meal);
		printf(" forkL:%p forkR:%p \n", prog->philos[i].fork_left, \
			prog->philos[i].fork_right);
		i++;
	}
}

long	ft_atoi(char *s)
{
	long	n;
	int		sign;

	sign = 1;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		s++;
	}
	n = 0;
	while (*s)
		n = (n * 10) + (*s++ - '0');
	return (n * sign);
}

static int	ft_is_num(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

void	check_is_num(char *s)
{
	if (!ft_is_num(s))
	{
		printf("Incorrect param., not positive int. \
			Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}
