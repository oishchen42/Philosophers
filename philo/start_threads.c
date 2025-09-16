/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 22:05:16 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	calculate_think(t_philo *philo)
{
	long	t_sleep;

	t_sleep = (philo->tteat * 3) - philo->ttsleep;
	print_thrd_msg(philo, "is thinking", 0);
	ft_sleep(t_sleep);
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (is_not_enough_time(philo))
		return (NULL);
	if (philo->is_odd && philo->id == philo->ph_max)
		init_wait(philo);
	if (philo->is_wait)
	{
		philo->is_wait = 0;
		init_wait(philo);
	}
	while (!philo_done(philo) && !is_prog_finished(philo->data))
	{
		philo_eat_think(philo);
		print_thrd_msg(philo, "is sleeping", 0);
		ft_sleep(philo->ttsleep);
		if (philo->is_odd && philo->tteat >= philo->ttsleep
			&& (philo->id == 1 || philo->id == philo->ph_max))
			calculate_think(philo);
	}
	pthread_mutex_lock(&philo->data->mutex_data);
	philo->data->eat_did++;
	pthread_mutex_unlock(&philo->data->mutex_data);
	return (NULL);
}

void	*tracer_routine(void *args)
{
	t_philo_struct	*data;
	int				i;
	long			cur_time;

	data = (t_philo_struct *)args;
	while (!is_all_finish_eating(data) && !is_prog_finished(data))
	{
		i = -1;
		while (++i < data->ph_n && !philo_done(&data->philos[i]))
		{
			pthread_mutex_lock(&data->mutex_lmeal);
			cur_time = get_time();
			if (cur_time - data->philos[i].tlast_meal > data->ttdie_msec)
			{
				pthread_mutex_lock(&data->mutex_data);
				anounce_death_stop_prog(data, i);
				pthread_mutex_unlock(&data->mutex_data);
				pthread_mutex_unlock(&data->mutex_lmeal);
				break ;
			}
			pthread_mutex_unlock(&data->mutex_lmeal);
		}
		usleep(500);
	}
	return (NULL);
}

int	start_prog(t_philo_struct *data)
{
	int		i;
	long	start_time;

	data->start_time = get_time();
	start_time = data->start_time;
	if (data->start_time == -1)
		return (non_thrd_er("data->start_time creation failed\n", 0));
	i = -1;
	while (++i < data->ph_n && start_time != -1)
	{
		data->philos[i].start_time = start_time;
		data->philos[i].tlast_meal = start_time;
		if (pthread_create(&data->philos[i].thrd, NULL,
				simple_routine, &data->philos[i]) == -1)
			return (clean_data(data, i), 0);
	}
	if (start_time != -1)
	{
		if (pthread_create(&data->death_tracer, NULL,
				tracer_routine, data) == -1)
			clean_data(data, i);
		data->is_thrd_tracer = 1;
	}
	return (1);
}
