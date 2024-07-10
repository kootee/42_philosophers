/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/07/10 09:12:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKES_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

typedef enum s_errorcode
{
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_INIT_ERROR = 201,
	EXIT_INVALID_ARGS = 202,
	EXIT_MUTEX_INIT_ERROR = 203,
	EXIT_THREADS_ERROR = 204,
	EXIT_MALLOC_FAIL = 205
}	t_errorcode;

typedef struct s_philo
{
	int				num;
	int				meal_count;
	unsigned int	ate_last;
	pthread_t		thread;
	pthread_t		monitor;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	m_eat;
	struct s_meta	*meta;
}	t_philo;

typedef struct s_meta
{
	int				stop;
	int				philos_num;
	int				times_to_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				full_philos;
	unsigned int	start_time;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_full_count;
	t_philo			*philo;
}	t_meta;

/* Init functions */
int				init_meta(t_meta *meta, char **argv);
int				init_philos(t_meta *meta, int num_of_philos);
int				valid_args(char **args, t_meta *meta);

/* Threads */
void			*philo_routine(void *ptr);
void			*monitor_life(void *ptr);

/* Utils */
unsigned int	get_time(void);
int				is_alive(t_philo *philo);
int				ft_atoi(const char *str);
void			ft_usleep(unsigned int time);
void			print_message(const char *message, t_philo *philo, int dead);
void			monitor_lock(t_philo *philo, int lock);
void			check_all_full(t_meta *meta);
void			*lonely_philo(t_philo *philo);

/* Error handling & terminate */
int				terminate(t_meta *meta);
int				handle_error(int errno, t_meta *meta);

#endif