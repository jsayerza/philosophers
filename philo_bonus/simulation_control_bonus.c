/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control_bonus.c                         :+:      :+:    :+:   */
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
	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has taken a fork", \
		prog_sems->print_sem);
	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "has taken a fork", \
		prog_sems->print_sem);
	print_msg(philo->philo_id, philo->start_time, "is eating 🍜 ", \
		prog_sems->print_sem);
	ft_usleep(philo->time_to_eat);
	sem_wait(philo->sems->die_sem);
	philo->last_meal = get_current_time();
	sem_post(philo->sems->die_sem);
	sem_wait(philo->sems->meal_sem);
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

void	philo_loop(t_philo *philo)
{
	philo_eat(philo, philo->sems);
	print_msg(philo->philo_id, philo->start_time, \
		"is sleeping 💤 ", philo->sems->print_sem);
	ft_usleep(philo->time_to_sleep);
	print_msg(philo->philo_id, philo->start_time, \
		"is thinking 💭 ", philo->sems->print_sem);
}

void	*philo_ctrl(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (true)
	{
		sem_wait(philo->sems->die_sem);
		if (get_current_time() - philo->last_meal > philo->time_to_die)
		{
			print_msg(philo->philo_id, philo->start_time, \
				RED"died!!! 💀 "RESET, philo->sems->print_sem);
			*philo->dead = 1;
			sem_post(philo->sems->die_sem);
			break ;
		}
		sem_post(philo->sems->die_sem);
	}
	return (NULL);
}
