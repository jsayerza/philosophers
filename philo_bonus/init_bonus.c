/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philosopher(t_prog *prog, t_philo *philo, int i)
{
	prog->philos[i].philo_id = i + 1;
	prog->philos[i].eating = false;
	prog->philos[i].meals_eaten = 0;
	prog->philos[i].dead = &prog->dead_flag;
	prog->philos[i].start_time = get_current_time();
	prog->philos[i].last_meal = prog->philos[i].start_time;
	prog->philos[i].time_to_die = prog->time_to_die;
	prog->philos[i].time_to_eat = prog->time_to_eat;
	prog->philos[i].time_to_sleep = prog->time_to_sleep;
	prog->philos[i].sems = prog->sems;
}

void	init_philos(t_prog *prog)
{
	int	i;

	prog->philos = malloc(sizeof(t_philo) * prog->num_philos);
	if (!prog->philos)
		destroy_and_free(prog, "Failed to allocate memory for philosophers", \
			true, true);
	i = 0;
	while (i < prog->num_philos)
	{
		init_philosopher(prog, &prog->philos[i], i);
		prog->proc_id[i] = -1;
		i++;
	}
}

void	init_sems(t_prog *prog)
{
	printf("Init_seems in\n");

	sem_unlink(DIE_SEM_NAME);
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(MEAL_SEM_NAME);
	sem_unlink(WRITE_SEM_NAME);

	prog->sems->die_sem = sem_open(DIE_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	prog->sems->fork_sem = sem_open(FORK_SEM_NAME, O_CREAT | O_EXCL, 0644, prog->num_philos);
	prog->sems->meal_sem = sem_open(MEAL_SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
	prog->sems->write_sem = sem_open(WRITE_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
//	printf("Init_seems 1 - prog->sems->die_sem:%p\n", prog->sems->die_sem);
//	printf("Init_seems 1 - prog->sems->fork_sem:%p\n", prog->sems->fork_sem);
	if (prog->sems->die_sem == SEM_FAILED || prog->sems->fork_sem == SEM_FAILED
		|| prog->sems->meal_sem == SEM_FAILED
		|| prog->sems->write_sem == SEM_FAILED)
			destroy_and_free(prog, "Failed to open sems", true, true);
//	printf("Init_seems 2\n");
	if (sem_unlink(DIE_SEM_NAME) == -1 || sem_unlink(FORK_SEM_NAME) == -1
		|| sem_unlink(MEAL_SEM_NAME) == -1 || sem_unlink(WRITE_SEM_NAME) == -1)
			destroy_and_free(prog, "Failed to unlink sems", true, true);
//	printf("Init_seems 3\n");
	printf("Init_seems out\n");
}

void	init_prog(t_prog *prog)
{
	printf("Init in - prog->num_philos:%d\n", prog->num_philos);
	prog->proc_id = (pid_t *)malloc(sizeof(pid_t) * prog->num_philos);
	prog->sems = (t_sems *)malloc(sizeof(t_sems));
	if (!prog->proc_id || !prog->sems)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
//	printf("Init 1 prog->sems:%p\n", prog->sems);
	init_sems(prog);
	printf("Init out\n");
}

void	init(t_prog *prog)
{
	prog->num_philos = 0;
	prog->time_to_die = 0;
	prog->time_to_eat = 0;
	prog->time_to_sleep = 0;
	prog->num_eats = 0;
	prog->dead_flag = false;
	// prog->proc_id = NULL;
	// prog->sems = NULL;
	// prog->philos = NULL;
}
