/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:16:28 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/26 17:07:13 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    valid_args(char **args)
{
    int i;
    int j;

    i = 1;
    while (args[i])
    {    
        j = 0;
        while (args[i][j])
        {
            if ((args[i][j] < '0' && args[i][j] > '9') || args[i][j] == '-')
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
/*     i = 0;
    while (i < num_of_philos)
    {
        if (pthread_join(meta->philo[i].thread, NULL) != 0)
            return (EXIT_FAILURE);
        i++;
    } */
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
            return(EXIT_FAILURE); // exiting here -> free the malloced philos
        if (pthread_mutex_init(&meta->philo[i].m_eat, NULL) != 0)
            return(EXIT_FAILURE); // exiting here -> free the malloced philos
        /* if (pthread_mutex_init(&meta->philo[i].m_dead, NULL) != 0)
            return(EXIT_FAILURE); */ // exiting here -> free the malloced philos
        // printf("right fork belongs to philo %d\n", (i + 1) % p_num);
        meta->philo[i].r_fork = &meta->philo[(i + 1) % p_num].l_fork;
        i++;
    }
    create_threads(meta, p_num);
    // printf("finished init philos\n");
    return (0);
}

int    init_meta(t_meta *meta, char **argv)
{
    meta->stop = false;
    meta->start_time = get_time();
    meta->full_philos = 0;
    meta->times_to_eat = -1;
    meta->philos_num = ft_atoi(argv[1]);
    meta->t_die = ft_atoi(argv[2]);
    meta->t_eat = ft_atoi(argv[3]);
    meta->t_sleep = ft_atoi(argv[4]);
    if (argv[5])
    {
        meta->times_to_eat = ft_atoi(argv[5]);
        if (meta->times_to_eat == 0)
            return (EXIT_FAILURE);
    }
    meta->philo = malloc(sizeof(t_philo) * meta->philos_num);
    if (meta->philo == NULL)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&meta->m_print, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&meta->m_stop, NULL) != 0)
        return (EXIT_FAILURE);
    if (pthread_mutex_init(&meta->m_full_count, NULL) != 0)
        return (EXIT_FAILURE);
    // printf("finished init meta\n");
    return (0);
}
