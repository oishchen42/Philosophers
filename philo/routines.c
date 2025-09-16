/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 21:36:43 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_wait(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking", 0);
	if (philo->tteat > ALARM_TIME)
		ft_sleep(philo->tteat - ALARM_TIME);
	else
		ft_sleep(philo->tteat);
}

int	is_not_enough_time(t_philo *philo)
{
	int	factor;
	int	tt_food;

	factor = 0;
	if (philo->id == philo->ph_max && philo->is_odd)
		factor += 1;
	factor += philo->is_wait;
	tt_food = philo->ttdie - (philo->tteat * factor);
	if ((tt_food <= 0 || philo->ph_max == 1))
	{
		pthread_mutex_lock(&philo->data->mutex_prog_finish);
		philo->data->is_prog_finish = 1;
		pthread_mutex_unlock(&philo->data->mutex_prog_finish);
		print_thrd_msg(philo, "is dead", 1);
		pthread_mutex_lock(&philo->data->mutex_lmsg);
		philo->data->is_death_anounced = 1;
		pthread_mutex_unlock(&philo->data->mutex_lmsg);
		return (1);
	}
	return (0);
}

void	ft_think(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking", 0);
	ft_sleep((philo->tteat * 2) - philo->ttsleep);
}

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
