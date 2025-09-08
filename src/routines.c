/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 18:08:56 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_sleep(t_philo *philo)
{
	long	cur_time;

	if (!is_dead_flg_raised(philo))
	{
		pthread_mutex_lock(&philo->data->msg_mutex);
		cur_time = get_time();
		if (cur_time == -1)
			return (0);
		printf("%ld %d is sleeping\n", cur_time - philo->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->msg_mutex);
		usleep(philo->ttsleep * 1000);
		return (1);
	}
	return (0);
}

int	is_alive(t_philo *philo)
{
	philo->tmeal = get_time();
	if (philo->tmeal == -1)
		return (e_msg("is_alive get_time failed\n", 0));
	if (philo->eat_did == 0)
		philo->tlast_meal = philo->start_time;
	//pthread_mutex_lock(&philo->data->msg_mutex);
	//printf("%d > %d is time of the uppcoming meal - time of the last meal\n", philo->tmeal - philo->tlast_meal, philo->ttdie);
	//pthread_mutex_unlock(&philo->data->msg_mutex);
	return (philo->tmeal - philo->tlast_meal < philo->ttdie);
}

void	massacre(t_philo *philo)
{
	int	i;

	i = 0;
	//print_thrd_msg(philo, "we are inside massacre");
	pthread_mutex_lock(&philo->data->finished_mutex);
	while (i < philo->ph_max)
	{
		philo->data->philos[i].is_dead = 1;
		i++;
	}
	pthread_mutex_unlock(&philo->data->finished_mutex);
}

int	philo_eat_think(t_philo *philo)
{
	//pthread_mutex_lock(&philo->data->msg_mutex);
	//printf("%d is inside philo_eat_think\n", philo->id);
	//pthread_mutex_unlock(&philo->data->msg_mutex);
	print_thrd_msg(philo, "is thinking");
	pthread_mutex_lock(philo->fork_1);
	print_thrd_msg(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_2);
	print_thrd_msg(philo, "has taken a fork");
	if (is_alive(philo))
	{
		print_thrd_msg(philo, "is eating");
		usleep(philo->tteat * 1000);
		philo->tlast_meal = get_time();
		if (philo->tlast_meal == -1)
			return (e_msg("get_time() failed", 0));
	}
	else
	{
		massacre(philo);
		print_thrd_msg(philo, "id_dead");
	}
	//print_thrd_msg(philo, "we are releasing the forsk\n");
	pthread_mutex_unlock(philo->fork_2);
	pthread_mutex_unlock(philo->fork_1);
	return (1);
}
