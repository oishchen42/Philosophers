/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:59:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/07 14:04:40 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_mallocs_forks(t_philo_struct *data, int fork_pos)
{
	if (fork_pos)
	{
		while (--fork_pos >= 0)
			pthread_mutex_destroy(&data->forks[fork_pos]);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->is_msg_mutex_ready)
		pthread_mutex_destroy(&data->msg_mutex);
	if (data->is_odd_mtx_ready)
		pthread_mutex_destroy(&data->odd_mutex);
	data->is_odd_mtx_ready = 0;
	data->is_msg_mutex_ready = 0;
}

void	clean_threads(t_philo_struct *data, int pos)
{
	printf("we are in the clean_thread\n");
	if (pos > 0)
	{
		while (--pos >= 0)
		{
			pthread_join(data->philos[pos].thrd, NULL);
		}
	}
}

void	clean_data(t_philo_struct *data)
{
	clean_threads(data, data->ph_n);
	clean_mallocs_forks(data, data->ph_n);
}
