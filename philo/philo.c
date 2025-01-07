/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:05:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/19 18:47:36 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	print_philos(prog.philos);
	destroy_and_free(&prog, NULL, false);
	return (EXIT_SUCCESS);
}
