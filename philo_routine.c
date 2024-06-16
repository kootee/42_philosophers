/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:12:50 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/16 15:43:33 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork)
}

void    *philo_routine(void *ptr)
{
	t_philo		*philo;
	pthread_t	thread;
	
	philo = (t_philo *)ptr;
    while (is_alive())
	{
		pthread_create(&thread, NULL, is_alive, ptr);
		grab_fork(philo);
		eat(philo);
		phtread_detach(thread);
		
	}
}