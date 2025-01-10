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

static void	start_simulation(t_prog *prog, int i)
{
	pthread_t	ctrl_die;
	t_philo		*philo;

	philo = &prog->philos[i];
	if (pthread_create(&ctrl_die, NULL, &philo_ctrl, philo) != 0)
		freer(prog, "Failed to create eats controller thread", \
			prog->num_philos, true);
	philo->start_time = prog->start_time;
	philo->last_meal = prog->start_time;
	if (i % 2 == 0)
		ft_usleep(1);
	while (*(philo->dead) == 0)
		philo_loop(philo);
	if (pthread_join(ctrl_die, NULL) != 0)
		freer(prog, "Failed to create eats controller thread", \
			prog->num_philos, true);
}

static void	*ctrl_eats_loop(void *ptr)
{
	t_prog	*prog;
	int		philos_ate_count;

	prog = (t_prog *)ptr;
	while (prog->exit_flag != 1)
	{
		philos_ate_count = 0;
		while (philos_ate_count < prog->num_philos)
		{
			sem_wait(prog->sems->meals_eaten_sem);
			philos_ate_count++;
		}
		prog->exit_flag = 1;
	}
	return (NULL);
}

void	simulation(t_prog *prog)
{
	pthread_t	ctrl_eats;
	pid_t		pid;
	int			i;

	if (prog->num_eats > 0)
	{
		if (pthread_create(&ctrl_eats, NULL, ctrl_eats_loop, prog) != 0)
			freer(prog, "Failed to create eats controller thread", \
				prog->num_philos, true);
		if (pthread_join(ctrl_eats, NULL) != 0)
			freer(prog, "Failed join thread", prog->num_philos, true);
	}
	prog->start_time = get_current_time();
	i = -1;
	while (++i < prog->philos[0].num_philos)
	{
		pid = fork();
		prog->proc_ids[i] = pid;
		if (pid == -1)
			freer(prog, "Failed to create philos processes", i, true);
		else if (pid == 0)
			start_simulation(prog, i);
	}
	waitpid(-1, NULL, 0);
	child_procs_kill(prog, prog->num_philos);
}
