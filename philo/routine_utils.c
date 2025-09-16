/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:51:22 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 18:47:55 by oishchen         ###   ########.fr       */
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

int	print_thrd_msg(t_philo *philo, char *msg, int is_urgent)
{
	long	cur_time;
	int		is_smone_dead;

	(void)is_urgent;
	is_smone_dead = 0;
	pthread_mutex_lock(&philo->data->mutex_lmsg);
	cur_time = get_time();
	is_smone_dead = philo->data->is_death_anounced;
	if (!is_smone_dead)
	{
		pthread_mutex_lock(&philo->data->mutex_msg);
		printf("%ld %d %s\n", cur_time - philo->start_time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->mutex_msg);
	}
	if (is_urgent)
		philo->data->is_death_anounced = 1;
	pthread_mutex_unlock(&philo->data->mutex_lmsg);
	return (1);
}

int	is_prog_finished(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_prog_finish);
	res = philo->data->is_prog_finish;
	pthread_mutex_unlock(&philo->data->mutex_prog_finish);
	return (res);
}

int	time_since_start(int time_since_start)
{
	int	new_time;

	new_time = get_time();
	//pthread_mutex_lock(&philo->data->msg_mutex);
	//printf("new_time - time_since_start: %d\n", new_time - time_since_start);
	//pthread_mutex_unlock(&philo->data->msg_mutex);
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

int	anounce_death_stop_prog(t_philo_struct *data, int philo)
{
	pthread_mutex_lock(&data->mutex_prog_finish);
	data->is_prog_finish = 1;
	pthread_mutex_unlock(&data->mutex_prog_finish);
	print_thrd_msg(&data->philos[philo], "is dead", 1);
	pthread_mutex_lock(&data->mutex_lmsg);
	data->is_death_anounced = 1;
	pthread_mutex_unlock(&data->mutex_lmsg);
	return (1);
}
