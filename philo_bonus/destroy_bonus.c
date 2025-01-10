/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sems_close_i(t_prog *prog)
{
	if (prog->sems->die_sem != SEM_FAILED)
	{
		sem_close(prog->sems->die_sem);
		sem_unlink("/die_sem");
	}
	if (prog->sems->fork_sem != SEM_FAILED)
	{
		sem_close(prog->sems->fork_sem);
		sem_unlink("/fork_sem");
	}
	if (prog->sems->meal_sem != SEM_FAILED)
	{
		sem_close(prog->sems->meal_sem);
		sem_unlink("/meal_sem");
	}
}

static void	sems_close_ii(t_prog *prog)
{
	if (prog->sems->meals_eaten_sem != SEM_FAILED)
	{
		sem_close(prog->sems->meals_eaten_sem);
		sem_unlink("/meals_eaten_sem");
	}
	if (prog->sems->print_sem != SEM_FAILED)
	{
		sem_close(prog->sems->print_sem);
		sem_unlink("/print_sem");
	}
	if (prog->sems->start_sem != SEM_FAILED)
	{
		sem_close(prog->sems->start_sem);
		sem_unlink("/start_sem");
	}
}

void	destroy_and_free(t_prog *prog)
{
	free(prog->sems);
	prog->sems = NULL;
	free(prog->philos);
	prog->philos = NULL;
	free(prog->proc_ids);
	prog->proc_ids = NULL;
}

void	child_procs_kill(t_prog *prog, int num_procs)
{
	while (--num_procs >= 0)
		if (prog->proc_ids[num_procs] != -1)
			kill(prog->proc_ids[num_procs], SIGKILL);
}

void	freer(t_prog *prog, char *msg, int num_procs, bool exit_fail)
{
	if (msg)
		printf("%s\n", msg);
	sems_close_i(prog);
	sems_close_ii(prog);
	destroy_and_free(prog);
	if (num_procs > 0)
		child_procs_kill(prog, num_procs);
	if (exit_fail)
		exit(EXIT_FAILURE);
}
