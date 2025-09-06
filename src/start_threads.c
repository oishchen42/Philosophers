/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/06 22:00:39 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_wait(t_philo_struct *data, int philo_id, char *msg)
{
	size_t	cur_time;

	cur_time = get_time();
	if (cur_time == -1)
		return (error_msg("gettime has failed\n", 0));
	pthread_mutex_lock(data->msg_mutex);
	printf("%lu %d %s\n", data->start_time - cur_time, philo_id, msg);
	pthread_mutex_unlock(data->msg_mutex);
	usleep(data->tteat_msec * 1000);
	return (1);
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while(philo->eat_did < philo->eat_needed && !is_dead(philo))
	{
		if (philo->is_odd && philo->eat_did > 0 && (philo->id == 1 || philo->id == philo->data->ph_n))
		{
			pthread_mutex_lock(philo->data->odd_mutex);
			philo_sleep(philo->data->tteat_msec, philo->data->start_time, philo->id);
			ptread_mutex_unloc(philo->data->odd_mutex);
		} // b_evo try to check by moivng it out of the while borders
		if (philo->is_wait)
		{
			philo->is_wait = 0;
			if (!init_wait(philo->data, philo->id, "is sleeping"))
				return (NULL);
		}
		if (!philo_eat_think(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		philo->eat_did++;
	}
	return (NULL);
}



int	start_prog(t_philo_struct *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	print_thrd_msg(data, -1, "The program is started"); // delete
	while (++i < data->ph_n)
	{
		if (data->ph_n > 3 && data->ph_n % 2 == 0)
			calculate_wait(&data->philos[i].id, 0);
		if (pthread_create(data->philos[i].thrd, NULL, &simple_routine, &data->philos[i]) == -1)
			return (clean_threads(data), e_msg("pthread_create failed\n", 0));
		//if (i == data->ph_n - 1)
		//	if (pthread_create(data->death_tracer, NULL, &tracer_routine, data->philos) == -1)
		//		return (clean_threads(data), e_msg("pthread_create failed\n", 0));
		return (0);
	}
}
