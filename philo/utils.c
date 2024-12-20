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

#include "philo.h"

int		ft_is_num(char *s)
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
        perror("Failed to get current time");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t time_to_sleep)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < time_to_sleep)
		usleep(500);
	return (0);
}