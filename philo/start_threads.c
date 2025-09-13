/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/13 15:55:56 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_wait(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking", 0);
	if (philo->tteat > ALARM_TIME)
		usleep((philo->tteat * 1000) - (ALARM_TIME * 1000));
	else
		usleep(philo->tteat * 1000);
}

static void	is_enough_time_for_meal(t_philo *philo)
{
	int	factor;
	int	tt_food;

	factor = 0;
	if (philo->id == philo->ph_max && philo->is_odd)
		factor += 1;
	factor += philo->is_wait;
	if ((philo->ttsleep <= philo->tteat && philo->is_odd)
		|| philo->tteat < ALARM_TIME)
		tt_food = philo->ttdie - (philo->tteat + philo->ttsleep + ALARM_TIME);
	else
		tt_food = philo->ttdie - (philo->tteat * factor);
	if ((tt_food <= 0 || philo->ph_max == 1))
	{
		massacre(philo);
		print_thrd_msg(philo, "is dead", 1);
		usleep(philo->ttdie * 1000);
	}
	if (philo->id == philo->ph_max)
	{
		pthread_mutex_lock(&philo->data->suspension_mutex);
		philo->data->is_all_ready = 1;
		pthread_mutex_unlock(&philo->data->suspension_mutex);
	}
}

static int	is_all_ready(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->suspension_mutex);
	res = philo->data->is_all_ready;
	pthread_mutex_unlock(&philo->data->suspension_mutex);
	return (res);
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	is_enough_time_for_meal(philo);
	while (!is_all_ready(philo))
		usleep(1 * 1000);
	if (philo->is_odd && philo->id == philo->ph_max)
		init_wait(philo);
	while (philo->eat_did < philo->eat_needed && !is_dead_flg_raised(philo))
	{
		if (philo->is_wait)
		{
			philo->is_wait = 0;
			init_wait(philo);
		}
		while (philo->is_odd && !is_odd_suspension(philo))
			usleep(1 * 1000);
		philo_eat_think(philo);
		if (philo->is_odd && (philo->id == 1 || philo->id == philo->ph_max))
			switch_is_odd_flg(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

int	start_prog(t_philo_struct *data)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->ph_n && data->start_time != -1)
	{
		data->philos[i].start_time = data->start_time;
		if (pthread_create(&data->philos[i].thrd, NULL,
				simple_routine, &data->philos[i]) == -1)
			return (clean_data(data, i),
				non_thrd_er("pthread_create failed\n", 0));
	}
	if (data->start_time == -1 && i == 0)
		return (non_thrd_er("data->start_time creation failed\n", 0));
	else if (data->start_time == -1)
		return (e_msg(&data->philos[i],
				"data->start_time creation failed\n", 0),
			clean_data(data, i), 0);
	return (1);
}
