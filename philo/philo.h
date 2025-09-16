/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:50:17 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 21:33:58 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo_struct	t_philo_struct;

typedef struct s_philo
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
	int				round;
	int				is_odd;
	int				ph_max;
	long			tlast_meal;
	int				tmeal;
	long			start_time;
	t_philo_struct	*data;
}	t_philo;

typedef struct s_philo_struct
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
	pthread_t		death_tracer;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_lmeal;
	pthread_mutex_t	mutex_msg;
	pthread_mutex_t	mutex_prog_finish;
	pthread_mutex_t	mutex_lmsg;
	pthread_mutex_t	mutex_data;
	int				ready_mtx_data;
	int				ready_mtx_lmsg;
	int				ready_mtx_prog_finish;
	int				ready_mtx_msg;
	int				ready_mtx_lmeal;
	int				is_thrd_tracer;
	int				is_forks_ready;
	int				is_prog_finish;
	int				is_death_anounced;
}	t_philo_struct;

# define FIRST_PHILO 1
# define LAST_PHILO 0
# define ALARM_TIME 10

// init_data && init_data_utils
int		init_data(t_philo_struct *data, int ac, char **av);
int		init_other_mtxs(t_philo_struct *data);

//cleanups
void	clean_mallocs_mutexes(t_philo_struct *data);
void	destroy_forks(t_philo_struct *data, int fork_pos);
void	clean_data(t_philo_struct *data, int pos);

//libft_utils
size_t	ft_strlen(const char *str);
int		p_atoi(char *str);

// error_handler
int		e_msg(t_philo *philo, char *msg, int exit_status);
int		non_thrd_er(char *msg, int exit_status);

// routine_utils
int		is_not_enough_time(t_philo *philo);
int		anounce_death_stop_prog(t_philo_struct *data, int philo);
int		is_all_finish_eating(t_philo_struct *data);
int		is_prog_finished(t_philo_struct *data);
int		print_thrd_msg(t_philo *philo, char *msg, int is_urgent);
int		philo_done(t_philo *philo);

// time routines
long	get_time(void);
void	ft_sleep(int time_to_sleep);

// deeds
void	philo_eat_think(t_philo *philo);
void	ft_think(t_philo *philo);
void	init_wait(t_philo *philo);

// starting program
int		start_prog(t_philo_struct *data);

#endif