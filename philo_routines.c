/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/17 11:26:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_philo(void *ptr)
{
	t_philo *philo;
	int	status;

	status = 0;
	philo = (t_philo *)ptr;
	if (philo->meal_count == philo->meta->times_to_eat \
		|| (get_time() - philo->ate_last) > philo->meta->t_die)
		status = 1;
	return (status);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meta->m_eat);
	pthread_mutex_lock(&philo->left_fork);
	printf("Philosopher %d is has picked up the left fork", philo->num);
	if (philo->meta->philos_num == 1)
	{
		ft_usleep(philo->meta->t_die);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	printf("Philosopher %d is has picked up the right fork", philo->num);
	philo->ate_last = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meta->m_eat);
	ft_usleep(philo->meta->t_eat);
	pthread_mutex_unlock(&philo->left_fork);
	printf("Philosopher %d is has put down the left fork", philo->num);
	pthread_mutex_unlock(philo->right_fork);
	printf("Philosopher %d is has put down the right fork", philo->num);
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	monitor;
	
	philo = (t_philo *)ptr;
    while (is_alive(philo))
	{
		pthread_create(&monitor, NULL, monitor_philo, ptr); // thread id, args, function to be executed, args passed to function
		eat(philo);
		printf("Philosopher %d is sleeping", philo->num);
		ft_usleep(philo->meta->t_sleep);
		printf("Philosopher %d is thinking", philo->num);
		phtread_detach(monitor);
	}
	return (ptr);
}