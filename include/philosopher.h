/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:50:17 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 15:54:14 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define E_FAIL 1
# define E_SUCCESS 0

typedef struct	s_philo
{
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
}	t_philo;

typedef struct	s_main_struct
{
	size_t			start_time;
	int				ph_n;
	int				ttdie_msec;
	int				tteat_msec;
	int				ttsleep_msec;
	int				eat_n;
	pthread_t		philos;
	pthread_mutex_t	forks;
}	t_main_struct;

size_t	ft_strlen(const char *str);
int		error_msg_exit_status(char *msg, int exit_status);
int		p_atoi(const char *arg_in_msec);

#endif 