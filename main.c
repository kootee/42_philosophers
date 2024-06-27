/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/27 13:47:15 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	terminate(t_meta *meta)
{
	int	i;

	i = 0;
	if (meta->philo == NULL || meta == NULL)
		return (0);
	while (i < meta->philos_num)
	{
		pthread_mutex_destroy(&meta->philo[i].l_fork);
		pthread_mutex_destroy(&meta->philo[i].m_eat);
		meta->philo[i].r_fork = NULL;
		meta->philo[i].meta = NULL;
		i++;
	}
	pthread_mutex_destroy(&meta->m_stop);
	pthread_mutex_destroy(&meta->m_full_count);
	pthread_mutex_destroy(&meta->m_print);
	free(meta->philo);
	meta->philo = NULL;
	return (0);
}

static int	join_threads(t_meta *meta)
{
	int	i;

	i = 0;
	while (i < meta->philos_num)
	{
		if (pthread_join(meta->philo[i].thread, NULL) != 0)
			return (EXIT_FAILURE);
		if (pthread_join(meta->philo[i].monitor, NULL) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_meta	meta;

	if (argc != 5 && argc != 6)
		return (handle_error(EXIT_CMD_COUNT_ERROR, &meta));
	if (valid_args(argv, &meta) != 0)
		return (handle_error(EXIT_INVALID_ARGS, &meta));
	if (init_meta(&meta, argv) != 0)
		return (handle_error(EXIT_INIT_ERROR, &meta));
	if (init_philos(&meta, meta.philos_num) != 0)
		return (handle_error(EXIT_THREADS_ERROR, &meta));
	if (join_threads(&meta))
		return (handle_error(EXIT_THREADS_ERROR, &meta));
	terminate(&meta);
	return (0);
}
