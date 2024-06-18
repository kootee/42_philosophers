/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/18 11:07:51 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_life(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	ft_usleep(philo->meta->t_die + 1);
	pthread_mutex_lock(&philo->meta->m_eat);
	pthread_mutex_lock(&philo->meta->m_stop);
	if (philo->eating == 0 && is_alive(philo) && \
		(get_time() - philo->ate_last >= (size_t)philo->meta->t_die))
	{
		pthread_mutex_unlock(&philo->meta->m_eat);
		pthread_mutex_unlock(&philo->meta->m_stop);
		printf("Philosopher %d died", philo->num);
		pthread_mutex_lock(&philo->meta->m_dead);
		philo->alive = 0;
		philo->meta->stop = 1;
		pthread_mutex_unlock(&philo->meta->m_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->meta->m_eat);
	pthread_mutex_unlock(&philo->meta->m_stop);
}

void	eat(t_philo *philo)
{
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		return ;
	}
	pthread_mutex_lock(&philo->left_fork);
	printf("Philosopher %d is has picked up the left fork", philo->num);
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d is has picked up the right fork", philo->num);
	philo->eating = 1;
	printf("Philosopher %d is eating", philo->num);
	pthread_mutex_lock(&philo->meta->m_eat);
	philo->ate_last = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meta->m_eat);
	ft_usleep(philo->meta->t_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d is has put down the right fork", philo->num);
	pthread_mutex_unlock(&philo->left_fork);
	printf("Philosopher %d is has put down the left fork", philo->num);
}

static void	philo_sleep_think(t_philo *philo)
{
	printf("Philosopher %d is sleeping", philo->num);
	ft_usleep(philo->meta->t_sleep);
	printf("Philosopher %d is thinking", philo->num);
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor_life;
	
	philo = (t_philo *)ptr;
	if (philo->meta->philos_num % 2 == 0)
		ft_usleep(10);
    while (is_alive(philo))
	{
		pthread_create(&monitor_life, NULL, monitor_life, ptr);
		eat(philo);
		phtread_detach(monitor_life);
		if (philo->meal_count == philo->meta->times_to_eat)
		{
			pthread_mutex_lock(&philo->meta->m_stop);
			philo->meta->full_philos++;
			if (philo->meta->full_philos == philo->meta->times_to_eat)
			{
				pthread_mutex_unlock(&philo->meta->m_stop);
				pthread_mutex_lock(&philo->meta->m_dead);
				philo->meta->stop = 1;
				pthread_mutex_unlock(&philo->meta->m_dead);
				return ;
			}
			pthread_mutex_unlock(&philo->meta->m_stop);
			return ;
		}
	}
}
