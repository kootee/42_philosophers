/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/24 14:08:52 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Keep checking if the philo is alive, meaning it's not currently eating
	and the time to die hasn't passed since the last meal */

void	*monitor_routine(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	while (philo->meta->stop != true) // other condition?
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
	pthread_mutex_lock(&philo->l_fork);
	print_message(TAKES_FORK, philo);
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_message(TAKES_FORK, philo);
	
	print_message(EATING, philo);
	pthread_mutex_lock(&philo->m_eat);
	philo->ate_last = get_time();
	philo->meal_count++;
	printf("Philo %d has eaten %d times now\n", philo->num, philo->meal_count);
	pthread_mutex_unlock(&philo->m_eat);
	ft_usleep(philo->meta->t_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
	printf("Philo %d has put the forks down\n", philo->num);
}

static void	philo_sleep_think(t_philo *philo)
{
	print_message(SLEEPING, philo);
	ft_usleep(philo->meta->t_sleep);
	print_message(THINKING, philo);
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
   /*  if (pthread_detach(monitor_thread) != 0)
        handle_error(EXIT_FAILURE); */
    while (is_alive(philo) && philo->meal_count != philo->meta->times_to_eat) // while meta->stop is false
	{
		eat(philo);
		if (philo->meal_count == philo->meta->times_to_eat)
		{
			printf("\033[1m philo %d is full \033[0m\n", philo->num);
			return (NULL);
		}
		philo_sleep_think(philo);
	}
	printf("\033[1mphilo %d is exiting\033[0m\n", philo->num);
	return (NULL);
}
