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
	char message[100];

	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "toke a fork", prog_sems->print_sem);
	sem_wait(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "toke a fork", prog_sems->print_sem);

	sem_wait(philo->sems->meal_sem);
	philo->eating = 1;
	sem_post(philo->sems->meal_sem);
	snprintf(message, sizeof(message), GREEN"is eating 🍜 --> %d"RESET, philo->eating);
	print_msg(philo->philo_id, philo->start_time, message, prog_sems->print_sem);

//	print_msg(philo->philo_id, philo->start_time, "is eating 🍜 ", prog_sems->print_sem);

	ft_usleep(philo->time_to_eat);

	sem_wait(philo->sems->meal_sem);
	philo->last_meal = get_current_time();
	philo->eating = 0;
	philo->meals_eaten++;
	// if (philo->meals_eaten >= philo->num_eats)
	// 	sem_post(philo->sems->meal_sem);
	sem_post(philo->sems->meal_sem);

	snprintf(message, sizeof(message), GREEN"ate --> %d Eating:%d Last_meal:%zu"RESET, \
		philo->meals_eaten, philo->eating, philo->last_meal);
	print_msg(philo->philo_id, philo->start_time, message, prog_sems->print_sem);

	sem_post(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "left a fork", prog_sems->print_sem);
	sem_post(prog_sems->fork_sem);
	print_msg(philo->philo_id, philo->start_time, "left a fork", prog_sems->print_sem);
}

void	start_philo_loop(t_philo *philo)
{
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	print_msg(philo->philo_id, philo->start_time, "start_philo_loop in ", philo->sems->print_sem);
	// if (philo->philo_id % 2 == 0)
	// 	ft_usleep(1);
	while (true)
	{
///////////////////////////
			sem_wait(philo->sems->meal_sem);
			if (get_current_time() - philo->last_meal > philo->time_to_die
				&& philo->eating == 0)
			{
				// snprintf(message, sizeof(message), "C_Time: %zu Elaps_t:%zu %ld Eating:%d", \
				// 	get_current_time(), get_current_time() - prog->philos[i].last_meal, \
				// 	prog->philos[i].time_to_die, prog->philos[i].eating);
				// print_msg(prog->philos[i].philo_id, prog->philos[i].start_time, message, prog->sems->print_sem);
				// snprintf(message, sizeof(message), "Last_t: %zu Elaps_t:%zu %ld Eating:%d", \
				// 	prog->philos[i].last_meal, get_current_time() - prog->philos[i].last_meal, \
				// 	prog->philos[i].time_to_die, prog->philos[i].eating);
				// print_msg(prog->philos[i].philo_id, prog->philos[i].start_time, message, prog->sems->print_sem);

				print_msg(philo->philo_id, philo->start_time, RED"died!!! 💀 "RESET, philo->sems->print_sem);
				sem_post(philo->sems->meal_sem);
				sem_wait(philo->sems->die_sem);
				*philo->dead = 1;
				sem_post(philo->sems->die_sem);
				break ;
			}
			sem_post(philo->sems->meal_sem);
//////////////////
		if (*philo->dead != 0)
			break ;
		print_msg(philo->philo_id, philo->start_time, "is thinking 💭 ", philo->sems->print_sem);
		philo_eat(philo, philo->sems);
		print_msg(philo->philo_id, philo->start_time, "is sleeping 💤 ", philo->sems->print_sem);
		ft_usleep(philo->time_to_sleep);
//		usleep(100);
	}
	printf(" start_philo_loop out (%d)\n", philo->philo_id);
	exit(0);
}

void	philos_create(t_prog *prog)
{
	int			i;

	printf("philos_create in\n");
	i = -1;
	while (++i < prog->num_philos)
	{
		prog->proc_ids[i] = fork();
		if (prog->proc_ids[i] == -1)
			destroy_and_free(prog, "Failed to create philos processes", false, true);
		else if (prog->proc_ids[i] == 0)
		{
			start_philo_loop(&prog->philos[i]);
			exit(0);
		}
	}
	printf("philos_create out\n");
}


void	start_controller_loop(t_prog *prog)
{
	int	i;
	char message[100];

	while (prog->exit_flag != 1) ;
	// {
	// 	i = -1;
	// 	while (++i < prog->num_philos)
	// 	{
	// 		// sem_wait(prog->philos[i].sems->meal_sem);
	// 		// if (get_current_time() - prog->philos[i].last_meal > prog->philos[i].time_to_die
	// 		// 	&& prog->philos[i].eating == 0)
	// 		// {
	// 		// 	snprintf(message, sizeof(message), "C_Time: %zu Elaps_t:%zu %ld Eating:%d", \
	// 		// 		get_current_time(), get_current_time() - prog->philos[i].last_meal, \
	// 		// 		prog->philos[i].time_to_die, prog->philos[i].eating);
	// 		// 	print_msg(prog->philos[i].philo_id, prog->philos[i].start_time, message, prog->sems->print_sem);
	// 		// 	snprintf(message, sizeof(message), "Last_t: %zu Elaps_t:%zu %ld Eating:%d", \
	// 		// 		prog->philos[i].last_meal, get_current_time() - prog->philos[i].last_meal, \
	// 		// 		prog->philos[i].time_to_die, prog->philos[i].eating);
	// 		// 	print_msg(prog->philos[i].philo_id, prog->philos[i].start_time, message, prog->sems->print_sem);

	// 		// 	print_msg(prog->philos[i].philo_id, prog->philos[i].start_time, RED"died!!! 💀 "RESET, prog->sems->print_sem);
	// 		// 	sem_post(prog->philos[i].sems->meal_sem);
	// 		// 	sem_wait(prog->sems->die_sem);
	// 		// 	prog->exit_flag = 1;
	// 		// 	sem_post(prog->sems->die_sem);
	// 		// 	break ;
	// 		// }
	// 		// sem_post(prog->philos[i].sems->meal_sem);

	// 		// 	sem_wait(prog->sems->die_sem);
	// 		// 	prog->exit_flag = 1;
	// 		// 	sem_post(prog->sems->die_sem);

	// 	}
	// }
//	sleep(1);
}

void	simulation(t_prog *prog)
{
	pid_t	controller_pid;
	int		i;

	print_philos(prog->philos);
	philos_create(prog);
	controller_pid = fork();
	if (controller_pid == -1)
		destroy_and_free(prog, "Failed to create controller process", true, true);
	if (controller_pid == 0)
	{
		start_controller_loop(prog);
		exit(0);
	}
	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < prog->num_philos)
		kill(prog->proc_ids[i], SIGTERM);
	//print_philos(prog.philos);
}
