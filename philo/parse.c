/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_is_num(char *s)
{
	if (!ft_is_num(s))
	{
		printf("Incorrect param., not positive int. Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_philos(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->num_philos = ft_atoi(s);
	if (prog->num_philos < 1 || prog->num_philos > 200)
	{
		printf("Incorrect param. Usage: ./philo #philos<1-200> #time_die #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_die(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_die = ft_atoi(s);
	if (prog->time_to_die < 1)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die > 0 #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_eat(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_eat = ft_atoi(s);
	if (prog->time_to_eat < 1)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die #time_eat > 0 #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_sleep(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_sleep = ft_atoi(s);
	if (prog->time_to_sleep < 1)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die #time_eat #time_sleep > 0 [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_num_eats(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->num_eats = ft_atoi(s);
	if (prog->num_eats < 1)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats > 0]\n");
		exit(EXIT_FAILURE);
	}
}