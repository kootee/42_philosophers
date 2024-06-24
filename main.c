/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/24 12:09:39 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    terminate(t_meta *meta)
{
    int i;

    i = 0;
    while(i < meta->philos_num)
    {
        pthread_mutex_destroy(&meta->philo[i].l_fork);
        //pthread_mutex_destroy(meta->philo[i].r_fork);
        pthread_mutex_destroy(&meta->philo[i].m_eat);
        pthread_mutex_destroy(&meta->philo[i].m_dead);
        meta->philo[i].r_fork = NULL;
        meta->philo[i].meta = NULL;
    }
    pthread_mutex_destroy(&meta->m_stop);
    pthread_mutex_destroy(&meta->m_print);
    pthread_mutex_destroy(&meta->m_full_philos);
    free(meta->philo);
}

int    main(int argc, char **argv)
{
    t_meta meta;
    
    if (argc != 5 && argc != 6)
        handle_error(EXIT_CMD_COUNT_ERROR);
    if (valid_args(argv) != 0)
        handle_error(EXIT_INVALID_ARGS);
    if (init_meta(&meta, argv) != 0)
    {
        // free
        handle_error(EXIT_INIT_ERROR);
    }
    init_philos(&meta, meta.philos_num);
    terminate(&meta);
}