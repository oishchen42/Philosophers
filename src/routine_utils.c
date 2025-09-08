/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 17:26:42 by oishchen         ###   ########.fr       */
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
		return (pthread_mutex_unlock(&philo->data->msg_mutex), e_msg("gettime has failed\n", 0));
	printf("%ld %d %s\n", cur_time - philo->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->msg_mutex);
	return (1);
}
