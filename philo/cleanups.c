/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:59:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 15:25:32 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_mallocs_mutexes(t_philo_struct *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->ready_mtx_data)
		pthread_mutex_destroy(&data->mutex_data);
	if (data->ready_mtx_msg)
		pthread_mutex_destroy(&data->mutex_msg);
	if (data->ready_mtx_prog_finish)
		pthread_mutex_destroy(&data->mutex_prog_finish);
	if (data->ready_mtx_lmeal)
		pthread_mutex_destroy(&data->mutex_lmeal);
	if (data->ready_mtx_lmsg)
		pthread_mutex_destroy(&data->mutex_lmsg);
	data->ready_mtx_data = 0;
	data->ready_mtx_msg = 0;
	data->ready_mtx_prog_finish = 0;
	data->ready_mtx_lmeal = 0;
	data->ready_mtx_lmsg = 0;
}

void	destroy_forks(t_philo_struct *data, int fork_pos)
{
	if (fork_pos > 0)
	{
		while (--fork_pos >= 0)
			pthread_mutex_destroy(&data->forks[fork_pos]);
	}
	data->is_forks_ready = 0;
	clean_mallocs_mutexes(data);
}

void	clean_data(t_philo_struct *data, int pos)
{
	if (data->is_thrd_tracer)
		pthread_join(data->death_tracer, NULL);
	if (pos > 0)
	{
		while (--pos >= 0)
			pthread_join(data->philos[pos].thrd, NULL);
	}
	destroy_forks(data, data->ph_n);
}
