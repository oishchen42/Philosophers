/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/13 14:43:17 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	if (!is_dead_flg_raised(philo))
	{
		print_thrd_msg(philo, "is sleeping", 0);
		usleep(philo->ttsleep * 1000);
	}
}

void	philo_eat_think(t_philo *philo)
{
	if (!is_dead_flg_raised(philo))
	{
		print_thrd_msg(philo, "is thinking", 0);
		if (is_alive(philo))
		{
			pthread_mutex_lock(philo->fork_1);
			print_thrd_msg(philo, "has taken a fork", 0);
			if (is_alive(philo))
			{
				pthread_mutex_lock(philo->fork_2);
				print_thrd_msg(philo, "has taken a fork", 0);
				if (is_alive(philo))
				{
					print_thrd_msg(philo, "is eating", 0);
					usleep(philo->tteat * 1000);
					philo->tlast_meal = get_time();
					philo->eat_did++;
				}
				pthread_mutex_unlock(philo->fork_2);
			}
			pthread_mutex_unlock(philo->fork_1);
		}
	}
}

void	switch_is_odd_flg(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->suspension_mutex);
	if (philo->data->odd_flg == LAST_PHILO)
		philo->data->odd_flg = FIRST_PHILO;
	else
		philo->data->odd_flg = LAST_PHILO;
	pthread_mutex_unlock(&philo->data->suspension_mutex);
}

int	is_odd_suspension(t_philo *philo)
{
	int	res;

	res = 0;
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->data->suspension_mutex);
		res = philo->data->odd_flg == FIRST_PHILO;
		pthread_mutex_unlock(&philo->data->suspension_mutex);
		return (res);
	}
	if (philo->id == philo->ph_max)
	{
		pthread_mutex_lock(&philo->data->suspension_mutex);
		res = philo->data->odd_flg == LAST_PHILO;
		pthread_mutex_unlock(&philo->data->suspension_mutex);
		return (res);
	}
	else
		return (1);
}
