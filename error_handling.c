/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:51:47 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/15 20:35:29 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    handle_error(int errno)
{
    if (errno == EXIT_CMD_COUNT_ERROR)
    {
        write(2, "Invalid amount of arguments", 28);
        exit(errno);
    }
    else if (errno == EXIT_INIT_ERROR)
    {
        write(2, "Init error", 11);
        exit(errno);
    }
}