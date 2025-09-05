/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:50:17 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 17:53:14 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# define E_FAIL 1
# define E_SUCCESS 0

typedef struct	s_philo
{
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
}	t_philo;

typedef struct	s_philo_struct
{
	size_t			start_time;
	int				ph_id;
	int				ph_n;
	int				ttdie_msec;
	int				tteat_msec;
	int				ttsleep_msec;
	int				eat_needed;
	int				eat_did;
	int				init_ttwait;
	pthread_t		*philos;
	pthread_t		*death_tracer;
	pthread_mutex_t	*forks;
}	t_philo_struct;

size_t	ft_strlen(const char *str);
int		e_msg(char *msg, int exit_status);
int		p_atoi(char *str);

#endif