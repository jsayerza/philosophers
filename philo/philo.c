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

void	init(t_prog *prog)
{
	prog->num_philos = 0;
	prog->time_to_die = 0;
	prog->time_to_eat = 0;
	prog->time_to_sleep = 0;
	prog->num_eats = 0;
}

int	main(int ac, char **av)
{
	//t_philo	philo;
	t_prog	prog;

	if (ac < 5 || (ac > 6))
	{
		printf("Incorrect num. of params. Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats]\n");
		return (EXIT_FAILURE);
	}
	init(&prog);
	parse_param_philos(&prog, av[1]);
	parse_param_die(&prog, av[2]);
	parse_param_eat(&prog, av[3]);
	parse_param_sleep(&prog, av[4]);
	if (ac == 6)
		parse_param_num_eats(&prog, av[5]);

	printf("num_philos: %d\n", prog.num_philos);
	printf("time_to_die: %d\n", prog.time_to_die);
	printf("time_to_eat: %d\n", prog.time_to_eat);
	printf("time_to_sleep: %d\n", prog.time_to_sleep);
	printf("num_eats: %d\n", prog.num_eats);
	return (EXIT_SUCCESS);
}
