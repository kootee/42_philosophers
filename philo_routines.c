/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/07/10 09:39:32 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_life(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		ft_usleep(philo->meta->t_die + 1);
		monitor_lock(philo, 1);
		if (philo->meta->stop == 1)
		{
			monitor_lock(philo, 0);
			break ;
		}
		if ((get_time() - philo->ate_last >= (long int)philo->meta->t_die))
		{
			philo->meta->stop = 1;
			monitor_lock(philo, 0);
			print_message(DIED, philo, 1);
			break ;
		}
		monitor_lock(philo, 0);
	}
	return (NULL);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKES_FORK, philo, 0);
	pthread_mutex_lock(&philo->l_fork);
	if (is_alive(philo) == 0)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	print_message(TAKES_FORK, philo, 0);
	pthread_mutex_lock(&philo->m_eat);
	print_message(EATING, philo, 0);
	philo->ate_last = get_time();
	philo->meal_count++;
	ft_usleep(philo->meta->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->m_eat);
	return (0);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo, 0);
	ft_usleep(philo->meta->t_sleep);
	print_message(THINKING, philo, 0);
}

void	*philo_routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (pthread_create(&philo->monitor, NULL, &monitor_life, philo) != 0)
		return (NULL);
	if (philo->meta->philos_num == 1)
		return (lonely_philo(philo));
	if (philo->num % 2 == 0)
		ft_usleep(philo->meta->t_sleep - 10);
	while (is_alive(philo))
	{
		if (eat(philo) != 0)
			break ;
		if (philo->meal_count == philo->meta->times_to_eat)
		{
			check_all_full(philo->meta);
			break ;
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
