/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/09 19:42:54 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_wait(t_philo *philo)
{
	print_thrd_msg(philo, "is tThinking");
	usleep(philo->tteat * 1000);
}

static void	is_enough_time_for_meal(t_philo *philo)
{
	int	factor;
	int	time_till_food;

	factor = 0;
	if (philo->id == philo->ph_max && philo->is_odd)
		factor += 1;
	factor += philo->is_wait;
	time_till_food = philo->ttdie - (philo->tteat * factor);
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
	if (philo->id == philo->ph_max && philo->is_odd)
		init_wait(philo);
	while (philo->eat_did < philo->eat_needed && !is_dead_flg_raised(philo))
	{
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
	if (data->start_time == -1 && i == 0)
		return (non_thrd_er("data->start_time creation failed\n", 0));
	else if (data->start_time == -1)
		return (e_msg(&data->philos[i], "data->start_time creation failed\n", 0),
			clean_data(data, i), 0);
	return (1);
}
