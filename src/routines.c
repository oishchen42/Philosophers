/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/06 22:02:58 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	size_t	cur_time;

	cur_time = get_time();
	if (cur_time == -1)
		return (0);
	printf("%d %d is sleeping\n", start_time - cur_time, ph_id);
	ft_sleep(ttsleep_msec);
}

int	philo_eat_think(t_philo *philo)
{
	if (!print_thrd_msg(philo->data, philo->id, "is thinking"))
		return (0);
	pthread_mutex_lock(philo->fork_1);
	if (!print_thrd_msg(philo->data, philo->id, "has taken a fork"))
		return (0);
	pthread_mutex_lock(philo->fork_2);
	if (!print_thrd_msg(philo->data, philo->id, "has taken a fork"))
		return (0);
	if (!print_thrd_msg(philo->data, philo->id, "is eating"))
		return (0);
	ft_sleep(philo->data->tteat_msec, philo->data->start_time, philo->id);
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_unlock(philo->fork_1);
	return (1);
}
