/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:50:17 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 18:19:23 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
#include <sys/time.h>

typedef struct s_philo_struct	t_philo_struct;

typedef struct	s_philo
{
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	pthread_t		thrd;
	int				id;
	int				eat_did;
	int				tteat;
	int				ttdie;
	int				ttsleep;
	int				eat_needed;
	int				is_wait;
	int				is_dead;
	int				is_odd;
	int				ph_max;
	int				tlast_meal;
	int				tmeal;
	long			start_time;
	t_philo_struct	*data;
}	t_philo;

typedef struct	s_philo_struct
{
	long			start_time;
	int				ph_n;
	int				ttdie_msec;
	int				tteat_msec;
	int				ttsleep_msec;
	int				eat_needed;
	int				eat_did;
	int				odd_flg;
	t_philo			*philos;
	pthread_mutex_t	finished_mutex;
	int				is_finished_mtx_ready;
	pthread_mutex_t	odd_mutex;
	int				is_odd_mtx_ready;
	pthread_mutex_t	*forks;
	int				is_forks_ready;
	pthread_mutex_t	msg_mutex;
	int				is_msg_mutex_ready;
}	t_philo_struct;

# define FIRST_PHILO 1
# define LAST_PHILO 0
# define ALARM_TIME 10

// init_data
int		init_data(t_philo_struct *data, int ac, char **av);

//cleanups
void	clean_mallocs_mutexes(t_philo_struct *data);
void	destroy_forks(t_philo_struct *data, int fork_pos);
void	clean_data(t_philo_struct *data, int pos);

//libft_utils
size_t	ft_strlen(const char *str);
int		p_atoi(char *str);

// error_handler
int		e_msg(char *msg, int exit_status);

// routine_utils
void	massacre(t_philo *philo);
int		is_dead_flg_raised(t_philo *philo);
long	get_time(void);
int		print_thrd_msg(t_philo *philo, char *msg);

// routines
int		philo_sleep(t_philo *philo);
int		philo_eat_think(t_philo *philo);

// starting program
int		start_prog(t_philo_struct *data);

#endif