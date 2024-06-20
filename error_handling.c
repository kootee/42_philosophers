/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:51:47 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/19 09:05:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    handle_error(int errno)
{
    if (errno == EXIT_CMD_COUNT_ERROR)
    {
        (void)!write(2, "Invalid amount of arguments\n", 29);
        exit(errno);
    }
    else if (errno == EXIT_INIT_ERROR)
    {
        (void)!write(2, "Error initialising\n", 20);
        exit(errno);
    }
    else if (errno == EXIT_INVALID_ARGS)
    {
        (void)!write(2, "Error initialising\n", 20);
        exit(errno);
    }
    else
    {
        (void)!write(2, "Philosophers: error\n", 21);
        exit(errno);
    }
}