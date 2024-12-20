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

void	print_philos(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		printf("Philo (%d):\n", prog->philos[i].philo_id);
		printf("  Eating: %d  Eaten: %d Time-eat: %d\n", prog->philos[i].eating, \
			prog->philos[i].meals_eaten, prog->philos[i].time_to_eat);
		printf("  last_meal: %ld\n", prog->philos[i].last_meal);
//		prog->philos[i].last_meal = 0;
//		prog->philos[i].thread = 0;
		i++;
	}
}

int	main(int ac, char **av)
{
	//t_philo	philo;
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

	printf("num_philos: %d\n", prog.num_philos);
	printf("time_to_die: %d\n", prog.time_to_die);
	printf("time_to_eat: %d\n", prog.time_to_eat);
	printf("time_to_sleep: %d\n", prog.time_to_sleep);
	printf("num_eats: %d\n", prog.num_eats);

	init_prog(&prog);
	init_forks(&prog);
	init_philos(&prog);
	thread_create(&prog);

	destroy_and_free(&prog, "", false);
	return (EXIT_SUCCESS);
}
