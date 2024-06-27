/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:51:47 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/27 13:48:09 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_error(int errno, t_meta *meta)
{
	if (errno == EXIT_CMD_COUNT_ERROR)
		(void)!write(2, "Invalid amount of arguments\n", 29);
	else if (errno == EXIT_INVALID_ARGS)
		(void)!write(2, "Invalid arguments\n", 19);
	else if (errno == EXIT_INIT_ERROR)
	{
		if (meta->philo != NULL)
			free(meta->philo);
		(void)!write(2, "Error initialising\n", 20);
	}
	else if (errno == EXIT_THREADS_ERROR)
	{
		(void)!write(2, "Error with threads\n", 20);
		terminate(meta);
	}
	else
	{
		if (meta->philo != NULL)
			free(meta->philo);
		(void)!write(2, "Philosophers: error\n", 21);
	}
	return (errno);
}
