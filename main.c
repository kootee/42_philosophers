/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/24 10:35:03 by ktoivola         ###   ########.fr       */
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
        pthread_mutex_destroy(meta->philo[i].r_fork);
        pthread_mutex_destroy(&meta->philo[i].m_eat);
        pthread_mutex_destroy(&meta->philo[i].m_dead);
    }
    free(meta->philo);
    pthread_mutex_destroy(&meta->m_stop);
    pthread_mutex_destroy(&meta->m_print);
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