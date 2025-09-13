/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/13 15:18:22 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tm;

	if (gettimeofday(&tm, NULL) == -1)
		return (-1);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	print_thrd_msg(t_philo *philo, char *msg, int is_urgent)
{
	long	cur_time;

	cur_time = get_time();
	if (is_urgent == 1)
	{
		pthread_mutex_lock(&philo->data->msg_mutex);
		if (!philo->data->is_death_anounced)
			philo->data->is_death_anounced = 1;
		else
			is_urgent = 0;
		pthread_mutex_unlock(&philo->data->msg_mutex);
	}
	if (is_urgent ||!is_dead_flg_raised(philo))
	{
		pthread_mutex_lock(&philo->data->msg_mutex);
		printf("%ld %d %s\n", cur_time - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->msg_mutex);
	}
	return (1);
}

int	is_alive(t_philo *philo)
{
	int	remain_time;

	philo->tmeal = get_time();
	if (philo->eat_did == 0)
		philo->tlast_meal = philo->start_time;
	remain_time = philo->tmeal - philo->tlast_meal;
	if (remain_time >= philo->ttdie)
	{
		massacre(philo);
		print_thrd_msg(philo, "is dead", 1);
		return (0);
	}
	return (1);
}

int	is_dead_flg_raised(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->finished_mutex);
	res = (philo->data->is_stop_exec);
	pthread_mutex_unlock(&philo->data->finished_mutex);
	return (res);
}

void	massacre(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->finished_mutex);
	philo->data->is_stop_exec = 1;
	pthread_mutex_unlock(&philo->data->finished_mutex);
}
