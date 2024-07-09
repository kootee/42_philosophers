/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:16:17 by ktoivola          #+#    #+#             */
/*   Updated: 2024/07/09 11:18:29 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(const char *message, t_philo *philo, int dead)
{
	unsigned int	current_time;

	if (!is_alive(philo) && dead != 1)
		return ;
	current_time = get_time() - philo->meta->start_time;
	pthread_mutex_lock(&philo->meta->m_print);
	printf("%u	%d %s\n", current_time, philo->num + 1, message);
	pthread_mutex_unlock(&philo->meta->m_print);
}

void	ft_usleep(unsigned int time)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
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

unsigned int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		(void)!write(2, "Get time of day error", 22);
		return (1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
