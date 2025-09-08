/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 19:51:46 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_wait(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking");
	usleep(philo->tteat * 1000);
}

static int	is_odd_suspension(t_philo *philo, int is_change_falg)
{
	if (philo->id == philo->ph_max || philo->id == 1)
	{
		pthread_mutex_lock(&philo->data->odd_mutex);
		if (philo->data->odd_flg == LAST_PHILO && philo->id == philo->ph_max)
		{
			print_thrd_msg(philo, "inside is_odd_supp logic");
			if (is_change_falg)
				philo->data->odd_flg = FIRST_PHILO;
			pthread_mutex_unlock(&philo->data->odd_mutex);
			return (1);
		}
		else if (philo->data->odd_flg == FIRST_PHILO && philo->id == 1)
		{
			if (is_change_falg)
				philo->data->odd_flg = LAST_PHILO;
			pthread_mutex_unlock(&philo->data->odd_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->data->odd_mutex);
	return (0);
}

static void	is_enough_time_for_meal(t_philo *philo)
{
	int	factor;
	int	time_till_food;

	factor = 0;
	if (philo->eat_did > 0 && philo->is_odd)
		factor += is_odd_suspension(philo, 0);
	factor += philo->is_wait;
	time_till_food = philo->ttdie - (philo->tteat + (philo->ttsleep * factor));
	if (time_till_food <= 0 || philo->ph_max == 1)
	{
		usleep(philo->ttdie * 1000);
		print_thrd_msg(philo, "is died");
		massacre(philo);
	}
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	is_enough_time_for_meal(philo);
	while (philo->eat_did < philo->eat_needed && !is_dead_flg_raised(philo))
	{
		if (philo->is_odd && is_odd_suspension(philo, 1))
			init_wait(philo);
		if (philo->is_wait)
		{
			philo->is_wait = 0;
			init_wait(philo);
		}
		philo_eat_think(philo);
		philo_sleep(philo);
		philo->eat_did++;
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
	return (1);
}
