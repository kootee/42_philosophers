/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:15:11 by ktoivola          #+#    #+#             */
/*   Updated: 2024/07/10 10:13:58 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_all_full(t_meta *meta)
{
	pthread_mutex_lock(&meta->m_full_count);
	meta->full_philos++;
	if (meta->full_philos == meta->philos_num)
	{
		pthread_mutex_lock(&meta->m_stop);
		meta->stop = 1;
		pthread_mutex_unlock(&meta->m_stop);
	}
	pthread_mutex_unlock(&meta->m_full_count);
}

int	is_alive(t_philo *philo)
{
	int	alive;

	pthread_mutex_lock(&philo->meta->m_stop);
	if (philo->meta->stop == 1)
		alive = 0;
	else
		alive = 1;
	pthread_mutex_unlock(&philo->meta->m_stop);
	return (alive);
}

void	monitor_lock(t_philo *philo, int lock)
{
	if (lock == 1)
	{
		pthread_mutex_lock(&philo->m_eat);
		pthread_mutex_lock(&philo->meta->m_stop);
	}
	else
	{
		pthread_mutex_unlock(&philo->m_eat);
		pthread_mutex_unlock(&philo->meta->m_stop);
	}
}

void	*lonely_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print_message(TAKES_FORK, philo, 0);
	ft_usleep(philo->meta->t_die);
	pthread_mutex_unlock(&philo->l_fork);
	return (NULL);
}
