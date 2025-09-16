/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:04:16 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 21:04:33 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_other_mtxs(t_philo_struct *data)
{
	if (pthread_mutex_init(&data->mutex_data, NULL) == -1)
		return (destroy_forks(data, data->ph_n), 0);
	data->ready_mtx_data = 1;
	if (pthread_mutex_init(&data->mutex_lmeal, NULL) == -1)
		return (destroy_forks(data, data->ph_n), 0);
	data->ready_mtx_lmeal = 1;
	if (pthread_mutex_init(&data->mutex_msg, NULL) == -1)
		return (destroy_forks(data, data->ph_n), 0);
	data->ready_mtx_msg = 1;
	if (pthread_mutex_init(&data->mutex_prog_finish, NULL) == -1)
		return (destroy_forks(data, data->ph_n), 0);
	data->ready_mtx_prog_finish = 1;
	if (pthread_mutex_init(&data->mutex_lmsg, NULL) == -1)
		return (destroy_forks(data, data->ph_n), 0);
	data->ready_mtx_lmsg = 1;
	return (1);
}
