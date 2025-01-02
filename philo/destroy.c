/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	prog_destroy_mutex(t_prog *prog)
{
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->print_lock);
}

void	forks_destroy_and_free(t_prog *prog)
{
	int	i;

	i = prog->num_philos;
	while (--i >= 0)
		pthread_mutex_destroy(&prog->forks[i]);
	free(prog->forks);
}

void	destroy_and_free(t_prog *prog, char *msg, bool exit_failure)
{
	if (msg)
		printf("%s\n", msg);
	free(prog->philos);
	forks_destroy_and_free(prog);
	prog_destroy_mutex(prog);
	if (exit_failure)
		exit(EXIT_FAILURE);
}
