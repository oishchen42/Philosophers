/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 20:55:32 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_thrd_msg(t_philo *philo, char *msg, int is_urgent)
{
	long	cur_time;
	int		is_smone_dead;

	(void)is_urgent;
	is_smone_dead = 0;
	pthread_mutex_lock(&philo->data->mutex_lmsg);
	cur_time = get_time();
	is_smone_dead = philo->data->is_death_anounced;
	if (!is_smone_dead && cur_time != -1)
	{
		pthread_mutex_lock(&philo->data->mutex_msg);
		printf("%ld %d %s\n", cur_time - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->mutex_msg);
	}
	if (is_urgent)
		philo->data->is_death_anounced = 1;
	pthread_mutex_unlock(&philo->data->mutex_lmsg);
	return (1);
}

int	anounce_death_stop_prog(t_philo_struct *data, int philo)
{
	pthread_mutex_lock(&data->mutex_prog_finish);
	data->is_prog_finish = 1;
	pthread_mutex_unlock(&data->mutex_prog_finish);
	print_thrd_msg(&data->philos[philo], "is dead", 1);
	pthread_mutex_lock(&data->mutex_lmsg);
	data->is_death_anounced = 1;
	pthread_mutex_unlock(&data->mutex_lmsg);
	return (1);
}
