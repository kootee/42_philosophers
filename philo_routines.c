/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/27 13:50:37 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Keep checking if the philo is alive, meaning it's not currently eating
	and the time to die hasn't passed since the last meal */

void	*monitor_life(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		ft_usleep(philo->meta->t_die + 1);
		pthread_mutex_lock(&philo->m_eat);
		pthread_mutex_lock(&philo->meta->m_stop);
		if(philo->meta->stop == true)
			break ; 
		if ((get_time() - philo->ate_last >= (long int)philo->meta->t_die))
		{
			philo->meta->stop = true;
			pthread_mutex_unlock(&philo->m_eat);
			pthread_mutex_unlock(&philo->meta->m_stop);
			print_message(DIED, philo, 1);
			break ;
		}
		pthread_mutex_unlock(&philo->m_eat);
		pthread_mutex_unlock(&philo->meta->m_stop);
	}
	pthread_mutex_unlock(&philo->m_eat);
	pthread_mutex_unlock(&philo->meta->m_stop);
	return (NULL);
}

static int	eat(t_philo *philo)
{
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		// pthread_mutex_unlock(&philo->l_fork);
		return (1);
	}
	
	pthread_mutex_lock(&philo->l_fork); // incorrect lock order
	print_message(TAKES_FORK, philo, 0);
	
	pthread_mutex_lock(philo->r_fork); // followed by aqusition by lock here...
	if (is_alive(philo) == 0)
	{
		// pthread_mutex_unlock(philo->r_fork);
		// pthread_mutex_unlock(&philo->l_fork);
		return (1);
	}
	print_message(TAKES_FORK, philo, 0);
	pthread_mutex_lock(&philo->m_eat);
	print_message(EATING, philo, 0);
	philo->ate_last = get_time();
	philo->meal_count++;
	ft_usleep(philo->meta->t_eat);
	pthread_mutex_unlock(&philo->m_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	
	// printf("Philo %d has eaten %d times now\n", philo->num, philo->meal_count);
	// printf("Philo %d has put the forks down\n", philo->num);
	return (0);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo, 0);
	ft_usleep(philo->meta->t_sleep);
	print_message(THINKING, philo, 0);
}

static void check_all_full(t_meta *meta)
{
	if (meta->full_philos == meta->philos_num)
	{
		// printf("Everyone is full\n");
		pthread_mutex_lock(&meta->m_stop);
		meta->stop = true;
		pthread_mutex_unlock(&meta->m_stop);
	}
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	
	philo = (t_philo *)ptr;
	// printf("Starting philo thread\n");
	if (philo->num % 2 == 0)
	{
		// printf("was uneven - sleeping 1 ms\n");
		ft_usleep(1); // time for eat - 10?
	}
	if (pthread_create(&philo->monitor, NULL, &monitor_life, philo) != 0)
		return (NULL);
    while (is_alive(philo) && philo->meal_count != philo->meta->times_to_eat)
	{
		if (eat(philo) != 0)
			break ;
		if (philo->meal_count == philo->meta->times_to_eat)
		{
			// printf("\033[1m philo %d is full \033[0m\n", philo->num);
			pthread_mutex_lock(&philo->meta->m_full_count);
			philo->meta->full_philos++;
			check_all_full(philo->meta);
			pthread_mutex_unlock(&philo->meta->m_full_count);
			break ;
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
