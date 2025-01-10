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

void	parse_param_philos(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->num_philos = ft_atoi(s);
	if (prog->num_philos < 1 || prog->num_philos > 200)
	{
		printf("Incorrect param. Usage: ./philo #philos<1-200> ");
		printf("#time_die #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_die(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_die = ft_atoi(s);
	if (prog->time_to_die < 60)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die >= 60 ");
		printf("#time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_eat(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_eat = ft_atoi(s);
	if (prog->time_to_eat < 60)
	{
		printf("Incorrect param. Usage: ./philo #philos ");
		printf("#time_die #time_eat >= 60 #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_sleep(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->time_to_sleep = ft_atoi(s);
	if (prog->time_to_sleep < 60)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die ");
		printf("#time_eat #time_sleep >= 60 [#eats]\n");
		exit(EXIT_FAILURE);
	}
}

void	parse_param_num_eats(t_prog *prog, char *s)
{
	check_is_num(s);
	prog->num_eats = ft_atoi(s);
	if (prog->num_eats < 1)
	{
		printf("Incorrect param. Usage: ./philo #philos #time_die ");
		printf("#time_eat #time_sleep [#eats > 0]\n");
		exit(EXIT_FAILURE);
	}
}
