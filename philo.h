/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:50:17 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/07 18:57:07 by oishchen         ###   ########.fr       */
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

# define E_FAIL 1
# define E_SUCCESS 0

typedef struct s_philo_struct	t_philo_struct;

typedef struct	s_philo
{
	pthread_mutex_t	*fork_1; //
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
	int				ttdie_msec;// b_evo do we need it?
	int				tteat_msec;// b_evo do we need it?
	int				ttsleep_msec;// b_evo do we need it?
	int				eat_needed;// b_evo do we need it?
	int				eat_did;// b_evo do we need it?
	int				odd_flg;// b_evo do we need it?
	t_philo			*philos;
	pthread_t		death_tracer;
	pthread_mutex_t	odd_mutex;
	int				is_odd_mtx_ready;
	pthread_mutex_t	*forks;
	int				is_forks_ready;
	pthread_mutex_t	msg_mutex;
	int				is_msg_mutex_ready;
}	t_philo_struct;

# define ODD_GLITCH 5
# define FIRST_PHILO 1
# define LAST_PHILO 0

// init_data
int		init_data(t_philo_struct *data, int ac, char **av);

//cleanups
void	clean_mallocs_forks(t_philo_struct *data, int fork_pos);
void	clean_threads(t_philo_struct *data, int pos);
void	clean_data(t_philo_struct *data);

//libft_utils
size_t	ft_strlen(const char *str);
int		p_atoi(char *str);

// error_handler
int		e_msg(char *msg, int exit_status);

// routine_utils
long	get_time(void);
int		print_thrd_msg(t_philo *philo, char *msg);

// routines
int		philo_sleep(t_philo *philo);
int		philo_eat_think(t_philo *philo);

// starting program
int		start_prog(t_philo_struct *data);

#endif