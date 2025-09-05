/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 17:51:17 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(int ttsleep_msec, int start_time, int ph_id)
{
	int	cur_time;

	cur_time = gettimeofday();
	printf("%d %d  is sleeping\n", start_time - cur_time, ph_id);
	ft_sleep(ttsleep_msec);
}

void	*philo_routine(t_philo_struct *data)
{
	if (data->eat_did == 0)
	{
		if (data->ph_id % 2 == 0)
			init_philo_wait(data->init_ttwait);

	}
	if (data->)
	ft_sleep(data->t)
}