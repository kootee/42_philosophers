/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/24 12:07:18 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Keep checking if the philo is alive, meaning it's not currently eating
	and the time to die hasn't passed since the last meal */

void	*monitor_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		ft_usleep(philo->meta->t_die + 1);
		//printf("monitor thread is checking philo %d\n", philo->num);
		pthread_mutex_lock(&philo->m_eat); // wait if the philo is currently eating
		if ((get_time() - philo->ate_last >= (long int)philo->meta->t_die))
		{
			pthread_mutex_unlock(&philo->m_eat);
			pthread_mutex_lock(&philo->meta->m_stop);
			philo->meta->stop = true;
			pthread_mutex_unlock(&philo->meta->m_stop);
			print_message(DIED, philo);
			break ;
		}
		pthread_mutex_unlock(&philo->m_eat);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		return ;
	}
	pthread_mutex_lock(&philo->l_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKES_FORK, philo);
	pthread_mutex_lock(&philo->m_eat);
	philo->eating = true;
	philo->ate_last = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->m_eat);
	print_message(EATING, philo);
	ft_usleep(philo->meta->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	philo->eating = false;
	printf("Philo %d has eaten %d times now\n", philo->num, philo->meal_count);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo);
	ft_usleep(philo->meta->t_sleep);
	print_message(THINKING, philo);
}
static void	check_all_finished_eating(t_philo *philo)
{
	if (philo->meta->full_philos == philo->meta->philos_num)
	{
		pthread_mutex_lock(&philo->meta->m_stop);
		philo->meta->stop = true;
		pthread_mutex_unlock(&philo->meta->m_stop);
	}
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor_thread;
	
	philo = (t_philo *)ptr;
	if (philo->meta->philos_num % 2 == 0)
		ft_usleep(10);
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, philo) != 0)
        handle_error(EXIT_FAILURE);
    if (pthread_detach(monitor_thread) != 0)
        handle_error(EXIT_FAILURE);
    while (is_alive(philo)) // while meta->stop is false
	{
		eat(philo);
		if (philo->meta->times_to_eat != 0 \
			&& philo->meal_count == philo->meta->times_to_eat)
		{
			pthread_mutex_lock(&philo->meta->m_full_philos);
			philo->meta->full_philos++;
			check_all_finished_eating(philo); // if yes --> stop is set in meta
			pthread_mutex_unlock(&philo->meta->m_full_philos);
			return (NULL);
		}
		philo_sleep_think(philo);
	}
	return (NULL);
}
