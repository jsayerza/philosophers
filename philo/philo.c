/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		perror("Failed to get current time");
	return ((size_t)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	ft_usleep(size_t time_to_sleep)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_to_sleep)
		usleep(500);
}

int	get_num_cpus(void)
{
	long	num_cpus;

	num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
	if (num_cpus < 0)
	{
		perror("Failed to get the number of CPUs");
		return (1);
	}
	return ((int)num_cpus);
}

int	get_current_cpu(void)
{
	int	cpu;

	cpu = sched_getcpu();
	if (cpu == -1)
	{
		perror("Failed to get the current CPU");
		return (1);
	}
	printf("<CPU:%d> ", cpu);
	return (0);
}

int	main(int ac, char **av)
{
	t_prog	prog;

	if (ac < 5 || (ac > 6))
	{
		printf("Incorrect num. of params. \
			Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats]\n");
		return (EXIT_FAILURE);
	}
	init(&prog);
	parse_param_philos(&prog, av[1]);
	parse_param_die(&prog, av[2]);
	parse_param_eat(&prog, av[3]);
	parse_param_sleep(&prog, av[4]);
	if (ac == 6)
		parse_param_num_eats(&prog, av[5]);
	init_prog(&prog);
	init_forks(&prog);
	init_philos(&prog);
	thread_create(&prog);
	print_philos(&prog);
	destroy_and_free(&prog, "", false);
	return (EXIT_SUCCESS);
}
