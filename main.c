/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:49:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/18 10:50:08 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free(t_meta *meta)
{
    int i;

    i = 0;
    while(i < meta->philos_num)
    {
        pthread_mutex_destroy(&meta->philo[i].left_fork);
        pthread_mutex_destroy(&meta->philo[i].right_fork);
    }
    free(meta->philo);
}

void    main(int argc, char **argv)
{
    t_meta meta;
    
    if (argc != 5 && argc != 6)
        handle_error(EXIT_CMD_COUNT_ERROR);
    if (!valid_args(argv))
        handle_error(EXIT_INVALID_ARGS);
    if (init_meta(&meta, argv) > 0)
    {
        // free
        handle_error(EXIT_INIT_ERROR);
    }
    init_philos(&meta, meta.philos_num);
    // free
}