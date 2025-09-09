/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:59:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/09 18:54:05 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_mallocs_mutexes(t_philo_struct *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->is_msg_mutex_ready)
		pthread_mutex_destroy(&data->msg_mutex);
	if (data->is_finished_mtx_ready)
		pthread_mutex_destroy(&data->finished_mutex);
	data->is_finished_mtx_ready = 0;
	data->is_msg_mutex_ready = 0;
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
	if (pos > 0)
	{
		while (--pos >= 0)
			pthread_join(data->philos[pos].thrd, NULL);
	}
	destroy_forks(data, data->ph_n);
}
