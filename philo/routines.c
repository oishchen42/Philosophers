/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:32:48 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 19:21:42 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat_think(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_prog_finish);
	res = philo->data->is_prog_finish;
	pthread_mutex_unlock(&philo->data->mutex_prog_finish);
	if (!res)
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

//void	switch_is_odd_flg(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->data->suspension_mutex);
//	if (philo->data->odd_flg == LAST_PHILO)
//		philo->data->odd_flg = FIRST_PHILO;
//	else
//		philo->data->odd_flg = LAST_PHILO;
//	pthread_mutex_unlock(&philo->data->suspension_mutex);
//}

//int	is_odd_suspension(t_philo *philo)
//{
//	int	res;

//	res = 0;
//	if (philo->id == 1)
//	{
//		pthread_mutex_lock(&philo->data->suspension_mutex);
//		res = philo->data->odd_flg == FIRST_PHILO;
//		pthread_mutex_unlock(&philo->data->suspension_mutex);
//		return (res);
//	}
//	if (philo->id == philo->ph_max)
//	{
//		pthread_mutex_lock(&philo->data->suspension_mutex);
//		res = philo->data->odd_flg == LAST_PHILO;
//		pthread_mutex_unlock(&philo->data->suspension_mutex);
//		return (res);
//	}
//	else
//		return (1);
//}
