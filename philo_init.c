/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:16:28 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/19 11:20:14 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    valid_args(char **args)
{
    int i;
    int j;

    i = 0;
    while (args[i])
    {    
        j = 0;
        while (args[i][j])
        {
            if (args[i][j] < '0' && args[i][j] > '9')
                return (EXIT_FAILURE);
            j++;
        }
        i++;
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
            return (EXIT_FAILURE);
        i++;
    }
    i = 0;
    while (i < num_of_philos)
    {
        if (pthread_join(meta->philo[i].thread, NULL) != 0)
            return (EXIT_FAILURE);
        i++;
    }
    return (0);
}

int init_philos(t_meta *meta, int philos_num)
{
    int i;

    i = 0;
    while (i < philos_num)
    {
        meta->philo[i].num = i + 1;
        meta->philo[i].alive = 1;
        meta->philo[i].eating = 0;
        meta->philo[i].meal_count = 0;
        meta->philo[i].ate_last = 0;
        // meta->philo[i].right_fork = NULL;
        meta->philo[i].meta = meta;
        if (pthread_mutex_init(&meta->philo[i].left_fork, NULL) != 0)
            return(EXIT_FAILURE); // exiting here -> free the malloced philos
        if (pthread_mutex_init(&meta->philo[i].m_eat, NULL) != 0)
            return(EXIT_FAILURE); // exiting here -> free the malloced philos
        if (pthread_mutex_init(&meta->philo[i].m_dead, NULL) != 0)
            return(EXIT_FAILURE); // exiting here -> free the malloced philos
        meta->philo[i].right_fork = &meta->philo[(i + 1) % philos_num].left_fork;
        i++;
    }
    create_threads(meta, philos_num);
    return (0);
}
/*      if (i == philos_num - 1)
            meta->philo[i].right_fork = &meta->philo[0].left_fork;
        else
            meta->philo[i].right_fork = &meta->philo[i + 1].left_fork; */

int    init_meta(t_meta *meta, char **argv)
{
    if (argv[5])
    {
        meta->times_to_eat = ft_atoi(argv[5]);
        if (meta->times_to_eat == 0)
            return (EXIT_FAILURE);
    }
    meta->start_time = get_time();
    meta->times_to_eat = 0;
    meta->philos_num = ft_atoi(argv[1]);
    meta->philo = malloc(sizeof(t_philo) * meta->philos_num);
    if (meta->philo == NULL)
        return (EXIT_FAILURE);
    meta->stop = 0;
    meta->full_philos = 0;
    meta->t_die = ft_atoi(argv[2]);
    meta->t_eat = ft_atoi(argv[3]);
    meta->t_sleep = ft_atoi(argv[4]);
    if (pthread_mutex_init(&meta->m_print, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&meta->m_stop, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&meta->m_full_philos, NULL) != 0)
        return (EXIT_FAILURE);
    return (0);
}
