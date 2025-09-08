/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 19:48:35 by oishchen         ###   ########.fr       */
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

int	print_thrd_msg(t_philo *philo, char *msg)
{
	long	cur_time;

	pthread_mutex_lock(&philo->data->msg_mutex);
	cur_time = get_time();
	if (cur_time == -1)
		return (pthread_mutex_unlock(&philo->data->msg_mutex),
			e_msg(philo, "gettime has failed\n", 0));
	printf("%ld %d %s\n", cur_time - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->msg_mutex);
	return (1);
}

int	is_alive(t_philo *philo)
{
	philo->tmeal = get_time();
	if (philo->eat_did == 0)
		philo->tlast_meal = philo->start_time;
	return (philo->tmeal - philo->tlast_meal < philo->ttdie);
}

int	is_dead_flg_raised(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->finished_mutex);
	res = (philo->is_dead || philo->data->is_stop_exec);
	pthread_mutex_unlock(&philo->data->finished_mutex);
	return (res);
}

void	massacre(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->data->finished_mutex);
	philo->data->is_stop_exec = 1;
	pthread_mutex_unlock(&philo->data->finished_mutex);
	pthread_mutex_lock(&philo->data->finished_mutex);
	while (i < philo->ph_max)
	{
		philo->data->philos[i].is_dead = 1;
		i++;
	}
	pthread_mutex_unlock(&philo->data->finished_mutex);
}
