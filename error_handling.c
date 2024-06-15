/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:51:47 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/12 17:13:16 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    handle_error(int errno)
{
    if (errno == EXIT_CMD_COUNT_ERROR)
    {
        printf("Invalid amount of arguments");
        exit(errno);
    }
    else if (errno == EXIT_INIT_ERROR)
    {
        printf("Init error");
        exit(errno);
    }
}