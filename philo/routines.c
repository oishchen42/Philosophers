/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 20:22:43 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_think(t_philo *philo)
{
	if (!is_prog_finished(philo->data))
	{
		print_thrd_msg(philo, "is thinking", 0);
		pthread_mutex_lock(philo->fork_1);
		print_thrd_msg(philo, "has taken a fork", 0);
		pthread_mutex_lock(philo->fork_2);
		print_thrd_msg(philo, "has taken a fork", 0);
		print_thrd_msg(philo, "is eating", 0);
		ft_sleep(philo->tteat);
		pthread_mutex_lock(&philo->data->mutex_lmeal);
		philo->eat_did++;
		philo->tlast_meal = get_time();
		pthread_mutex_unlock(&philo->data->mutex_lmeal);
		pthread_mutex_unlock(philo->fork_2);
		pthread_mutex_unlock(philo->fork_1);
	}
}

