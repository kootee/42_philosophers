/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:16:17 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/17 10:37:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(unsigned int time)
{
	unsigned int	start;
	
	start = get_time();
	while (get_time() - start < time)
		usleep(500);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		nbr;

	i = 1;
	nbr = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str - 48;
		str++;
	}
	return (nbr * i);
}

bool    valid_args(char **args)
{
    if (0)
        return (true);
    else
        return (false);
}

size_t  get_time(void)
{
    struct timeval   time;
    
    if (gettimeofday(&time, NULL) < 0)
        handle_error(EXIT_FAILURE);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}