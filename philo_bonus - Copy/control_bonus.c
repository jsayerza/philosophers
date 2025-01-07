/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*control_ate(void *ptr)
{
	t_prog	*prog;
	int		philos_ate_count;

	printf("control_ate in\n");
	prog = (t_prog *)ptr;
	philos_ate_count = 0;
	printf("control_ate 1\n");
	while (true)
	{
		printf("control_ate 2\n");
		sem_wait(prog->sems->meal_sem);
		printf("control_ate 3\n");
		philos_ate_count++;
		if (philos_ate_count >= prog->num_philos)
			break ;
	}
	printf("control_ate out\n");
	return (NULL);
}

static void	set_exit_flag(t_philo *philo)
{
	sem_wait(philo->sems->die_sem);
	*philo->dead = 1;
	sem_post(philo->sems->die_sem);

}

static void	set_dead(t_philo *philo, t_sems *prog_sems)
{
	sem_post(philo->sems->die_sem);
	print_msg(philo->philo_id, philo->start_time, "died!!! 💀 ", prog_sems->print_sem);
	set_exit_flag(philo);
}

// void	*control_die(void *ptr)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)ptr;
// 	while (true)
// 	{
// 			sem_wait(philo->sems->die_sem);
// 			if (((get_current_time() - philo->last_meal) > philo->time_to_die)
// 				&& (philo->eating == false))
// 			{
// 				set_dead(philo);
// 				return (NULL);
// 			}
// 			sem_post(philo->sems->die_sem);
// 	}
// 	set_exit_flag(philo);
// 	return (NULL);
// }

void	*control_die(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	printf("control_die in philo (%d) [%ld] timetodie:%ld\n", \
		philo->philo_id, get_current_time() - philo->last_meal, philo->time_to_die);
	while (true)
	{
			sem_wait(philo->sems->die_sem);
			printf("control_die IN philo (%d) [%ld] timetodie:%ld\n", \
				philo->philo_id, get_current_time() - philo->last_meal, philo->time_to_die);
			if (((get_current_time() - philo->last_meal) > philo->time_to_die))
			{
				printf("control_die DEAD philo (%d)\n", philo->philo_id);
				print_philosopher(philo);
				printf("  cur_time:   %ld\n", get_current_time());
//				set_dead(philo);
				pause();
				return (NULL);
			}
			sem_post(philo->sems->die_sem);
	}
	set_exit_flag(philo);
	printf("control_die out\n");
	return (NULL);
}
