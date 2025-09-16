/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_finsihed_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:54:41 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 20:56:15 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_prog_finished(t_philo_struct *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_prog_finish);
	res = data->is_prog_finish;
	pthread_mutex_unlock(&data->mutex_prog_finish);
	return (res);
}

int	philo_done(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_lmeal);
	res = philo->eat_did == philo->eat_needed;
	pthread_mutex_unlock(&philo->data->mutex_lmeal);
	return (res);
}

int	is_all_finish_eating(t_philo_struct *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_data);
	res = data->eat_did == data->ph_n;
	pthread_mutex_unlock(&data->mutex_data);
	return (res);
}
