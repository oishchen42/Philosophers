/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 10:50:41 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_wait(t_philo *philo)
{
	long	cur_time;

	cur_time = get_time();
	if (cur_time == -1)
		return (e_msg("gettime has failed\n", 0));
	print_thrd_msg(philo, "is sleeping");
	usleep(philo->tteat * 1000);
	return (1);
}

int	is_odd_suspension(t_philo *philo, int is_change_falg)
{
	if(philo->id == philo->ph_max || philo->id == 1)
	{
		pthread_mutex_lock(&philo->data->odd_mutex);
		if (philo->data->odd_flg == LAST_PHILO && philo->id == philo->ph_max)
		{
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
		pthread_mutex_unlock(&philo->data->odd_mutex);
	}
	return (0);
}

void	is_enough_time_for_meal(t_philo *philo)
{
	int	factor;
	int	time_till_food;

	factor = 0;
	if (philo->eat_did > 0)
		factor += is_odd_suspension(philo, 0);
	else
		factor += philo->is_wait;
	time_till_food = philo->ttdie - (philo->ttsleep * factor);
	if (time_till_food <= 0)
	{
		usleep(philo->ttdie * 1000);
		print_thrd_msg(philo, "is died");
		philo->is_dead = 1;
	}
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	is_enough_time_for_meal(philo);
	printf("philo %d, philo->is_wait %d\n", philo->id, philo->is_wait);
	while(philo->eat_did < philo->eat_needed && !philo->is_dead)
	{
		//pthread_mutex_lock(&philo->data->msg_mutex);
		//printf("%d philo has started his job\n", philo->id);
		//pthread_mutex_unlock(&philo->data->msg_mutex);
		if (is_odd_suspension(philo, 1))
			philo_sleep(philo); // b_evo try to check by moivng it out of the while borders
		if (philo->is_wait)
		{
			philo->is_wait = 0;
			if (!init_wait(philo))
				return (NULL);
		}
		if (!philo_eat_think(philo))
			return (NULL);
		if (!philo->is_dead)
			if (!philo_sleep(philo))
				return (NULL);
		philo->eat_did++;
	}
	pthread_mutex_lock(&philo->data->msg_mutex);
	printf("%d philo has FINISHED his job\n", philo->id);
	pthread_mutex_unlock(&philo->data->msg_mutex);
	return (NULL);
}



int	start_prog(t_philo_struct *data)
{
	int	i;

	data->start_time = get_time();
	printf("%lu the program has began\n", data->start_time); // delete
	i = -1;
	while (++i < data->ph_n)
	{
		data->philos[i].start_time = data->start_time;
		if (pthread_create(&data->philos[i].thrd, NULL, simple_routine, &data->philos[i]) == -1)
			return (clean_threads(data, i), e_msg("pthread_create failed\n", 0));
		//pthread_mutex_lock(&data->msg_mutex);
		//printf("%d circle is finished\n", i);
		//pthread_mutex_unlock(&data->msg_mutex);
	}
	return (1);
}
