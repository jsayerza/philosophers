/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:20:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/11/20 16:02:59 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

long	ft_atoi(char *s)
{
	long	n;
	int		sign;

	sign = 1;
	if (s[0] == '-' || s[0] == '+')
	{
		if (s[0] == '-')
			sign = -1;
		s++;
	}
	n = 0;
	while (*s)
		n = (n * 10) + (*s++ - '0');
	return (n * sign);
}

static int	ft_is_num(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

void	check_is_num(char *s)
{
	if (!ft_is_num(s))
	{
		printf("Incorrect param., not positive int. \
			Usage: ./philo #philos #time_die #time_eat #time_sleep [#eats]\n");
		exit(EXIT_FAILURE);
	}
}
