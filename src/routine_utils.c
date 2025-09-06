/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/06 21:59:29 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(ttsleep_msc)
{
	usleep(ttsleep_msc * 1000);
}

size_t	get_time(void)
{
	struct timeval	tm;

	if (gettimeofday(&tm, NULL) == -1)
		return (-1);
	return (tm.tv_sec * 1000 + tm.tv_usec / 1000);
}

int	print_thrd_msg(t_philo_struct *data, int philo_id, char *msg)
{
	size_t	cur_time;

	if (cur_time == -1)
		return (error_msg("gettime has failed\n", 0));
	pthread_mutex_lock(data->msg_mutex);
	printf("%lu %d %s\n", data->start_time - cur_time, philo_id, msg);
	pthread_mutex_unlock(data->msg_mutex);
}
void	calculate_wait(t_philo *philo)
{
	if (philo->eat_did % 2 == 0)
	{
		if (philo->id % 2 == 0)
			philo->is_wait = 1;
	}
}

