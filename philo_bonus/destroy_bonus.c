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
	if (prog->sems->die_sem != SEM_FAILED)
		sem_close(prog->sems->die_sem);
	if (prog->sems->fork_sem != SEM_FAILED)
		sem_close(prog->sems->fork_sem);
	if (prog->sems->meal_sem != SEM_FAILED)
		sem_close(prog->sems->meal_sem);
	if (prog->sems->write_sem != SEM_FAILED)
		sem_close(prog->sems->write_sem);
}

void	destroy_and_free(t_prog *prog, char *msg, bool isParentProc, \
	bool exit_failure)
{
	int	i;

	printf("dest_free in - prog->num_philos:%d\n", prog->num_philos);
	i = -1;
	if (isParentProc)
	{
//		printf("dest_free 1\n");
		while (++i < prog->num_philos)
		{
//			printf("dest_free [%d]\n", i);
			if (prog->proc_id[i] != -1)
			{
//				printf("dest_free kill:[%d]\n", i);
				kill(prog->proc_id[i], SIGKILL);
			}
		}
	}
	sems_close(prog);
//	printf("dest_free 2\n");
	i = -1;
	free(prog->sems);
	free(prog->philos);
	free(prog->proc_id);
//	printf("dest_free 3\n");
	if (msg)
		printf("%s\n", msg);
	printf("dest_free out\n");
	if (exit_failure)
		exit(EXIT_FAILURE);
}
