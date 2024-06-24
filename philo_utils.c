/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:16:17 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/24 11:49:40 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->meta->m_stop);
	if (philo->meta->stop == true)
	{
		pthread_mutex_unlock(&philo->meta->m_stop);
		return (0);
	}
	pthread_mutex_unlock(&philo->meta->m_stop);
    return (1);
}

void	print_message(const char *message, t_philo *philo)
{
    size_t current_time;

    /* if (!is_alive(philo))
        return ; */
    current_time = get_time() - philo->meta->start_time;
    pthread_mutex_lock(&philo->meta->m_print);
    printf("%zu %d %s\n", current_time, philo->num, message);
    pthread_mutex_unlock(&philo->meta->m_print);
}

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

long int  get_time(void)
{
    struct timeval   time;
    
    if (gettimeofday(&time, NULL) < 0)
        handle_error(EXIT_FAILURE);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}