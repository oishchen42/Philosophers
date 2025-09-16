/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:53:25 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 20:54:19 by oishchen         ###   ########.fr       */
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

int	time_since_start(int time_since_start)
{
	int	new_time;

	new_time = get_time();
	return (new_time - time_since_start);
}

void	ft_sleep(int time_to_sleep)
{
	long	cur_time;

	if (time_to_sleep <= 0)
		return ;
	cur_time = get_time();
	while (time_since_start(cur_time) < time_to_sleep)
		usleep(500);
}
