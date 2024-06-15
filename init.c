/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:16:28 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/14 22:09:12 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philos(t_meta *meta)
{
    int i;

    meta->start_time = timestamp();
    i = 0;
    while (i < meta->philos_num)
    {
        meta->philos[i].num = i + 1;
        meta->philos[i].meal_count = 0;
        meta->philos[i].ate_last = 0;
        meta->philos[i].right_fork = NULL;
        if (pthread_mutex_init(&(meta->philos[i].left_fork), NULL) > 0);
            
    }
}

int    init_meta(t_meta *meta, char **argv)
{
    pthread_mutex_init(&meta->print, NULL);
    pthread_mutex_init(&meta->m_eat, NULL);
    pthread_mutex_init(&meta->m_stop, NULL);
    pthread_mutex_init(&meta->dead, NULL);
    meta->philos_num = atoi(argv[1]);
    meta->t_die = atoi(argv[2]);
    meta->t_eat = atoi(argv[3]);
    meta->t_sleep = atoi(argv[4]);
    if (argv[5])
    {
        meta->n_eat = atoi(argv[5]);
        if (meta->n_eat == 0)
            return (1);
    }
    meta->philos = malloc(sizeof(t_philo) * meta->philos_num);
    if (meta->philos == NULL)
        return (EXIT_MALLOC_FAIL);
    meta->stop = false;
    meta->eats = false;
}
