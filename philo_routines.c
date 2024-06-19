/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/19 10:59:32 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_life(void *ptr)
{
	/* needs to be loop */
	t_philo *philo;

	philo = (t_philo *)ptr;
	ft_usleep(philo->meta->t_die + 1);
	pthread_mutex_lock(&philo->m_eat);
	pthread_mutex_lock(&philo->meta->m_stop);
	if (philo->eating == 0 && is_alive(philo) && \
		(get_time() - philo->ate_last >= (long int)philo->meta->t_die))
	{
		pthread_mutex_unlock(&philo->m_eat);
		pthread_mutex_unlock(&philo->meta->m_stop);
		print_message(DIED, philo);
		pthread_mutex_lock(&philo->meta->m_dead);
		philo->alive = 0;
		philo->meta->stop = 1;
		pthread_mutex_unlock(&philo->meta->m_dead);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->m_eat);
	pthread_mutex_unlock(&philo->meta->m_stop);
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(philo->right_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(&philo->m_eat);
	philo->eating = 1;
	print_message(EATING, philo);
	philo->ate_last = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_eat);
	ft_usleep(philo->meta->t_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo);
	ft_usleep(philo->meta->t_sleep);
	print_message(THINKING, philo);
}
static int	check_all_finished_eating(t_philo *philo)
{
			pthread_mutex_lock(&philo->meta->m_stop);
			philo->meta->full_philos++;
			if (philo->meta->full_philos == philo->meta->philos_num) // if all philos are full
			{
				pthread_mutex_unlock(&philo->meta->m_stop);
				pthread_mutex_lock(&philo->meta->m_dead);
				philo->meta->stop = 1;
				pthread_mutex_unlock(&philo->meta->m_dead);
				pthread_detach(monitor_thread);
				return (NULL);
			}
			pthread_mutex_unlock(&philo->meta->m_stop);
	
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;
	
	philo = (t_philo *)ptr;
	if (philo->meta->philos_num % 2 == 0)
		ft_usleep(10);
	pthread_create(&monitor_thread, NULL, monitor_life, ptr);
    while (is_alive(philo))
	{
		eat(philo);
		if (philo->meta->times_to_eat != 0 \ 
			&& philo->meal_count == philo->meta->times_to_eat)
		{
			pthread_mutex_lock()
			check_all_finished_eating(philo); // if yes --> stop is set in meta
			pthread_detach(monitor_thread);
			return (NULL);
		}
		philo_sleep_think(philo);
	}
	pthread_detach(monitor_thread);
	return (NULL);
}
