/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/09 19:36:41 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	long	cur_time;

	if (!is_dead_flg_raised(philo))
	{
		cur_time = get_time();
		pthread_mutex_lock(&philo->data->msg_mutex);
		printf("%ld %d is sleeping\n", cur_time - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->msg_mutex);
		usleep(philo->ttsleep * 1000);
	}
}

void	philo_eat_think(t_philo *philo)
{
	if (!is_dead_flg_raised(philo))
	{
		print_thrd_msg(philo, "is thinking");
		pthread_mutex_lock(philo->fork_1);
		print_thrd_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_2);
		print_thrd_msg(philo, "has taken a fork");
		if (is_alive(philo))
		{
			print_thrd_msg(philo, "is eating");
			usleep(philo->tteat * 1000);
			pthread_mutex_unlock(philo->fork_2);
			pthread_mutex_unlock(philo->fork_1);
			philo->tlast_meal = get_time();
		}
		else
		{
			pthread_mutex_unlock(philo->fork_2);
			pthread_mutex_unlock(philo->fork_1);
			massacre(philo);
			print_thrd_msg(philo, "is dead");
		}
	}
}
