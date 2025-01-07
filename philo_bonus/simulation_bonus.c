/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_philo *philo, t_sems *prog_sems)
{
	char	message[100];

	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has taken a fork", \
		prog_sems->print_sem);
	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has taken a fork", \
		prog_sems->print_sem);
	print_msg(philo->philo_id, philo->start_time, "is eating 🍜 ", \
		prog_sems->print_sem);
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->sems->meal_sem);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->num_eats)
		sem_post(prog_sems->meals_eaten_sem);
	sem_post(philo->sems->meal_sem);
	sem_post(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has put down a fork", \
		prog_sems->print_sem);
	sem_post(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has put down a fork", \
		prog_sems->print_sem);
}

void	start_philo_loop(t_philo *philo)
{
	char	message[100];

	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	while (true)
	{
		sem_wait(philo->sems->meal_sem);
		if (get_current_time() - philo->last_meal > philo->time_to_die)
		{
			print_msg(philo->philo_id, philo->start_time, \
				RED"died!!! 💀 "RESET, philo->sems->print_sem);
			sem_post(philo->sems->meal_sem);
			sem_wait(philo->sems->die_sem);
			*philo->dead = 1;
			sem_post(philo->sems->die_sem);
			break ;
		}
		sem_post(philo->sems->meal_sem);
		print_msg(philo->philo_id, philo->start_time, \
			"is thinking 💭 ", philo->sems->print_sem);
		philo_eat(philo, philo->sems);
		print_msg(philo->philo_id, philo->start_time, \
			"is sleeping 💤 ", philo->sems->print_sem);
		ft_usleep(philo->time_to_sleep);
	}
}

void	philos_create(t_prog *prog)
{
	int			i;

	i = -1;
	while (++i < prog->num_philos)
	{
		prog->proc_ids[i] = fork();
		if (prog->proc_ids[i] == -1)
			freer(prog, "Failed to create philos processes", i, true);
		else if (prog->proc_ids[i] == 0)
			start_philo_loop(&prog->philos[i]);
	}
}

static void	controller_loop(t_prog *prog)
{
	int	philos_ate_count;

	while (prog->exit_flag != 1)
	{
		if (prog->num_eats > 0)
		{
			philos_ate_count = 0;
			while (philos_ate_count < prog->num_philos)
			{
				sem_wait(prog->sems->meals_eaten_sem);
				philos_ate_count++;
			}
			prog->exit_flag = 1;
		}
	}
}

void	simulation(t_prog *prog)
{
	pid_t	controller_pid;

	philos_create(prog);
	controller_pid = fork();
	if (controller_pid == -1)
		freer(prog, "Failed to create controller process", \
			prog->num_philos, true);
	if (controller_pid == 0)
	{
		controller_loop(prog);
	}
	waitpid(-1, NULL, 0);
	child_procs_destroy(prog, prog->num_philos);
}
