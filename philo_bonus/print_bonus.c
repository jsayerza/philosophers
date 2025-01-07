/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:20:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/20 16:02:59 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_msg(int philo_id, size_t start_time, char *s, sem_t *semt)
{
	sem_wait(semt);
	printf("%zu %d %s\n", get_current_time() - start_time, philo_id, s);
	sem_post(semt);
}

void	print_msg_detailed(char *s, t_philo *philo)
{
	size_t	cur_time;
	size_t	elapsed;
	size_t	elapsed_last_meal;

	sem_wait(philo->sems->print_sem);
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
	sem_post(philo->sems->print_sem);
}

void	print_philosopher(t_philo *philo)
{
	int	sem_value;

	printf("Philo (%d):\n", philo->philo_id);
	printf("  Eaten: %d\n", philo->meals_eaten);
	printf("  #philos: %d #eats: %d\n", \
		philo->num_philos, philo->num_eats);
	printf("  #t_die: %ld #t_eat: %ld #t_sleep: %ld\n", \
		philo->time_to_die, philo->time_to_eat, philo->time_to_sleep);
	printf("  start_time: %zu\n", \
		philo->start_time);
	printf("  last_meal : %zu \n", \
		philo->last_meal);
	sem_getvalue(philo->sems->die_sem, &sem_value);
	printf("  DIE  sem_status: %d\n", sem_value);
	sem_getvalue(philo->sems->meal_sem, &sem_value);
	printf("  MEAL sem_status: %d\n", sem_value);
	sem_getvalue(philo->sems->print_sem, &sem_value);
	printf("  PR   sem_status: %d\n", sem_value);
	sem_getvalue(philo->sems->fork_sem, &sem_value);
	printf("  FORK sem_status: %d\n", sem_value);
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
