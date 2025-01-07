/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_philo *philo)
{
	printf("philo_eat in (%d)\n", philo->philo_id);
	sem_wait(philo->sems->fork_sem);
	print_msg("toke a fork", philo);
	sem_wait(philo->sems->fork_sem);
	print_msg("toke a fork", philo);
	sem_wait(philo->sems->die_sem);
	philo->eating = true;
	sem_post(philo->sems->die_sem);
	print_msg("is eating 🍜 ", philo);
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->sems->die_sem);
	philo->last_meal = get_current_time();
	philo->eating = false;
	sem_post(philo->sems->die_sem);
	sem_wait(philo->sems->meal_sem);
	philo->meals_eaten++;
	sem_post(philo->sems->meal_sem);
	if (philo->meals_eaten >= philo->num_eats)
		sem_post(philo->sems->meal_sem);
	sem_post(philo->sems->fork_sem);
	print_msg("left a fork", philo);
	sem_post(philo->sems->fork_sem);
	print_msg("left a fork", philo);
	printf("philo_eat out (%d)\n", philo->philo_id);
}

static void	philo_loop(t_philo	*philo)
{
	printf("philo_loop in (%d)\n", philo->philo_id);
	philo_eat(philo);
	print_msg("is sleeping 💤 ", philo);
	ft_usleep(philo->time_to_sleep);
	print_msg("is thinking 💭 ", philo);
	printf("philo_loop out (%d)\n", philo->philo_id);
}

void	start_philo_loop(t_prog *prog, int i)
{
	t_philo		*philo;
	pthread_t	controller_die;

	printf("start_philo_loop in (%d)\n", i);
	philo = &prog->philos[i];
	if (pthread_create(&controller_die, NULL, &control_die, philo) != 0
		|| pthread_join(controller_die, NULL) != 0)
		destroy_and_free(prog, "Failed die controller thread", false, true);
	printf("start_philo_loop 1 (%d)\n", i);
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	if (philo->philo_id % 2 == 0)
		ft_usleep(1);
	while (true)
	{
		sem_wait(philo->sems->die_sem);
		if (*philo->dead != 0)
		{
			printf("start_philo_loop DEAD (%d)\n", i);
			sem_post(philo->sems->die_sem);
			break ;
		}
		sem_post(philo->sems->die_sem);
		philo_loop(philo);
	}
	printf("start_philo_loop out (%d)\n", i);
}

void	thread_create(t_prog *prog)
{
	pthread_t	controller_ate;
	int			i;

	printf("thread_create in\n");
	if (prog->num_eats > 0)
	{
		printf("thread_create 1\n");
		if (pthread_create(&controller_ate, NULL, &control_ate, prog) != 0)
			destroy_and_free(prog, "Failed to create controller thread", true, true);
		if (pthread_join(controller_ate, NULL) != 0)
			destroy_and_free(prog, "Failed to join controller thread", true, true);
	}
	printf("thread_create 2\n");
	i = 0;
	while (i < prog->num_philos)
	{
		prog->proc_ids[i] = fork();
		if (prog->proc_ids[i] == -1)
			destroy_and_free(prog, "Failed to create philos' processes", true, true);
		if (prog->proc_ids[i] == -0)
			start_philo_loop(prog, i);
		i++;
	}
	printf("thread_create 3\n");
	waitpid(-1, NULL, 0);
	printf("thread_create out\n");
}
