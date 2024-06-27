/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:16:28 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/27 13:56:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    valid_args(char **args, t_meta *meta)
{
    int i;
    int j;

    i = 1;
    while (args[i])
    {   
        j = 0;
        while (args[i][j])
        {
            if (!(args[i][j] >= '0' && args[i][j] <= '9'))
                return (EXIT_INVALID_ARGS);
            j++;
        }
        i++;
    }
    meta->times_to_eat = -1;
    if (args[5])
    {
        meta->times_to_eat = ft_atoi(args[5]);
        if (meta->times_to_eat == 0)
            return (EXIT_INVALID_ARGS);
    }
    return (0);
}

static int create_threads(t_meta *meta, int num_of_philos)
{
    int i;
    
    i = 0;
    while (i < num_of_philos)
    {
        if (pthread_create(&meta->philo[i].thread, NULL, \
            &philo_routine, &meta->philo[i]) != 0)
            return (EXIT_THREADS_ERROR);
        i++;
    }
    return (0);
}

int init_philos(t_meta *meta, int p_num)
{
    int i;

    i = 0;
    while (i < p_num)
    {
        meta->philo[i].num = i;
        meta->philo[i].meta = meta;
        meta->philo[i].meal_count = 0;
        meta->philo[i].r_fork = NULL;
        meta->philo[i].ate_last = meta->start_time;
        if (pthread_mutex_init(&meta->philo[i].l_fork, NULL) != 0)
            return(EXIT_MUTEX_INIT_ERROR);
        if (pthread_mutex_init(&meta->philo[i].m_eat, NULL) != 0)
            return(EXIT_MUTEX_INIT_ERROR);
        if (meta->philos_num > 1)
            meta->philo[i].r_fork = &meta->philo[(i + 1) % p_num].l_fork;
        i++;
    }
    if (create_threads(meta, p_num) != 0)
        return (EXIT_THREADS_ERROR);
    return (0);
}

int    init_meta(t_meta *meta, char **argv)
{
    meta->stop = false;
    meta->philo = NULL;
    meta->full_philos = 0;
    meta->t_die = ft_atoi(argv[2]);
    meta->t_eat = ft_atoi(argv[3]);
    meta->t_sleep = ft_atoi(argv[4]);
    meta->philos_num = ft_atoi(argv[1]);
    meta->start_time = get_time();
    meta->philo = malloc(sizeof(t_philo) * meta->philos_num);
    if (meta->philo == NULL)
        return (EXIT_MALLOC_FAIL);
    if (pthread_mutex_init(&meta->m_print, NULL) != 0)
        return (EXIT_MUTEX_INIT_ERROR);
    if (pthread_mutex_init(&meta->m_stop, NULL) != 0)
        return (EXIT_MUTEX_INIT_ERROR);
    if (pthread_mutex_init(&meta->m_full_count, NULL) != 0)
        return (EXIT_MUTEX_INIT_ERROR);
    return (0);
}
