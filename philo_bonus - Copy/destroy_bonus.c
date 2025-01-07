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

static void	sems_close(t_prog *prog)
{
	// if (sem_unlink(DIE_SEM_NAME) == -1 || sem_unlink(FORK_SEM_NAME) == -1
	// 	|| sem_unlink(MEAL_SEM_NAME) == -1 || sem_unlink(WRITE_SEM_NAME) == -1)
	// 		destroy_and_free(prog, "Failed to unlink sems", true, true);
	if (prog->sems->die_sem != SEM_FAILED)
		sem_close(prog->sems->die_sem);
	if (prog->sems->fork_sem != SEM_FAILED)
		sem_close(prog->sems->fork_sem);
	if (prog->sems->meal_sem != SEM_FAILED)
		sem_close(prog->sems->meal_sem);
	if (prog->sems->print_sem != SEM_FAILED)
		sem_close(prog->sems->print_sem);
}

void	destroy_and_free(t_prog *prog, char *msg, bool isParentProc, \
	bool exit_failure)
{
	int	i;

	printf("dest_free in - prog->num_philos:%d\n", prog->num_philos);
	if (msg)
		printf("%s\n", msg);
	i = -1;
	if (isParentProc)
	{
		printf("dest_free 1\n");
		while (++i < prog->num_philos)
		{
			printf("dest_free [%d]\n", i);
			if (prog->proc_ids[i] != -1)
			{
				printf("dest_free kill:[%d]\n", i);
				kill(prog->proc_ids[i], SIGKILL);
			}
		}
	}
	sems_close(prog);
	printf("dest_free 2\n");
	// i = -1;
	// while (++i < prog->num_philos)
	// 	free(prog->philos[i]);
	free(prog->sems);
	free(prog->philos);
	free(prog->proc_ids);
//	printf("dest_free 3\n");
	printf("dest_free out\n");
	if (exit_failure)
		exit(EXIT_FAILURE);
}
