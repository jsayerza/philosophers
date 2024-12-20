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
		printf("  Eating: %d  Eaten: %d\n", prog->philos[i].eating, prog->philos[i].meals_eaten);
//		prog->philos[i].last_meal = 0;
//		prog->philos[i].thread = 0;
		i++;
	}
}

void	init_philos(t_prog *prog)
{
	int	i;

	printf("prog->num_philos:%d\n", prog->num_philos);

	prog->philos = malloc(sizeof(t_philo) * prog->num_philos);
    if (!prog->philos)
	{
        perror("Failed to allocate memory for philosophers");
        exit(EXIT_FAILURE);
    }
	i = 0;
	while (i < prog->num_philos)
	{
		prog->philos[i].philo_id = i + 1;
		prog->philos[i].eating = false;
		prog->philos[i].meals_eaten = 0;
//		prog->philos[i].last_meal = 0;
//		prog->philos[i].thread = 0;
		i++;
	}
	print_philos(prog);
}

void	init(t_prog *prog)
{
	prog->num_philos = 0;
	prog->time_to_die = 0;
	prog->time_to_eat = 0;
	prog->time_to_sleep = 0;
	prog->num_eats = 0;
	prog->philos = NULL;
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

//	init_prog(&prog);
//	init_forks(&prog);
	init_philos(&prog);

	free(prog.philos);
	return (EXIT_SUCCESS);
}
