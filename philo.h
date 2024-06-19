/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/06/19 09:44:47 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>       // For printf
#include <stdlib.h>      // For malloc, free
#include <string.h>      // For memset
#include <unistd.h>      // For write, usleep
#include <sys/time.h>    // For gettimeofday
#include <pthread.h>     // For pthread functions
#include <stdbool.h>
#include <sys/time.h>

typedef enum s_errorcode
{
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_INIT_ERROR = 201,
	EXIT_INVALID_ARGS = 202,
	EXIT_INVALID_MAP_DIM = 203,
	EXIT_OPEN_ERROR = 204,
	EXIT_INVALID_FILE_NAME = 205,
	EXIT_MALLOC_FAIL = 206
}	t_errorcode;

typedef	struct s_philo
{
	pthread_t		thread;
	int				num;
	int				alive;
	int				eating;
	int				meal_count;
	long int		ate_last;
	struct s_meta	*meta; // includes time to die eat and sleep
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
}	t_philo;

typedef struct s_meta
{
	long int		start_time;
	int				philos_num;
	int				times_to_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				stop;
	int				full_philos;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_stop; 
	t_philo			*philo;
}	t_meta;

/* Init functions */
int	init_meta(t_meta *meta, char **argv);
int init_philos(t_meta *meta, int num_of_philos);
int	valid_args(char **args);

/* Philo routines */
void    *philo_routine(void *ptr);
int		is_alive(t_philo *philo);

/* Utils */
int	ft_atoi(const char *str);
int	ft_usleep(unsigned int time);

/* Error handling */
void	handle_error(int errno);
size_t  get_time(void);

#endif