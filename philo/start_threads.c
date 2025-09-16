/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:37:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 19:50:12 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_wait(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking", 0); // delete
	if (philo->tteat > ALARM_TIME)
		ft_sleep(philo->tteat - ALARM_TIME);
	else
		ft_sleep(philo->tteat);
}

//static void	is_enough_time_for_meal(t_philo *philo)
//{
//	int	factor;
//	int	tt_food;

//	factor = 0;
//	if (philo->id == philo->ph_max && philo->is_odd)
//		factor += 1;
//	factor += philo->is_wait;
//	tt_food = philo->ttdie - (philo->tteat * factor);
//	if ((tt_food <= 0 || philo->ph_max == 1))
//	{
//		anounce_death_stop_prog(philo->data, philo->id);
//	}
//	//if (philo->id == philo->ph_max)
//	//{
//	//	pthread_mutex_lock(&philo->data->suspension_mutex);
//	//	philo->data->is_all_ready = 1;
//	//	pthread_mutex_unlock(&philo->data->suspension_mutex);
//	//}
//}

//void	calc_next_wait(t_philo *philo)
//{
//	int	res;

//	ft_sleep(philo, (philo->tteat * 2) - philo->ttsleep);
	//pthread_mutex_lock(&philo->data->mutex_data);
	//if (philo->data->odd_flg == philo->id % philo->ph_max)
	//{
	//	res = 1;
	//	philo->data->odd_flg = philo->id == philo->ph_max
	//}
	//pthread_mutex_unlock(&philo->data->mutex_data);
//}

void	ft_think(t_philo *philo)
{
	print_thrd_msg(philo, "is thinking", 0);
	ft_sleep((philo->tteat * 2) - philo->ttsleep);
}

int	ate_all(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->mutex_lmeal);
	res = philo->eat_did == philo->eat_needed;
	pthread_mutex_unlock(&philo->data->mutex_lmeal);
	return (res);
}

void	*simple_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	//is_enough_time_for_meal(philo);
	if (philo->is_odd && philo->id == philo->ph_max)
		init_wait(philo);
	if (philo->is_wait)
	{
		philo->is_wait = 0;
		init_wait(philo);
	}
	while (!ate_all(philo) && !is_prog_finished(philo))
	{
		philo_eat_think(philo);
		print_thrd_msg(philo, "is sleeping", 0);
		ft_sleep(philo->ttsleep);
		if (philo->is_odd && philo->tteat >= philo->ttsleep
		&& (philo->id == 1 || philo->id == philo->ph_max))
			ft_think(philo);
	}
	pthread_mutex_lock(&philo->data->mutex_data);
	philo->data->eat_did++;
	pthread_mutex_unlock(&philo->data->mutex_data);
	return (NULL);
}

int	is_finish_eating(t_philo_struct *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_data);
	res = data->eat_did == data->eat_needed;
	pthread_mutex_unlock(&data->mutex_data);
	return (res);
}

void	*tracer_routine(void *args)
{
	t_philo_struct	*data;
	int				i;
	int				is_all_ate;

	data = (t_philo_struct *)args;
	is_all_ate = 0;
	while (!is_all_ate)
	{
		i = -1;
		pthread_mutex_lock(&data->mutex_data);
		is_all_ate = data->eat_did == data->eat_needed;
		pthread_mutex_unlock(&data->mutex_data);
		int	ateall = 0;
		while (++i < data->ph_n && !ateall)
		{
			pthread_mutex_lock(&data->mutex_lmeal);
			ateall = data->philos[i].eat_did == data->philos[i].eat_needed;
			pthread_mutex_unlock(&data->mutex_lmeal);
			pthread_mutex_lock(&data->mutex_lmeal);
			if (get_time() - data->philos[i].tlast_meal >= data->ttdie_msec)
			{
				pthread_mutex_lock(&data->mutex_data);
				is_all_ate = anounce_death_stop_prog(data, i);
				pthread_mutex_unlock(&data->mutex_data);
				pthread_mutex_unlock(&data->mutex_lmeal);
				break ;
			}
			pthread_mutex_unlock(&data->mutex_lmeal);
			is_all_ate = is_finish_eating(data);
		}
	}
	return (NULL);
}

//void	*waiter_routine(void *args)
//{
//	t_philo_struct	*data;

//	data = (t_philo_struct *)args;
//	{
		
//	}
//}

int	start_prog(t_philo_struct *data)
{
	int		i;
	long	ttime;
	int		ph_n;

	data->start_time = get_time();
	ttime = data->start_time;
	ph_n = data->ph_n;
	if (data->start_time == -1)
		return (non_thrd_er("data->start_time creation failed\n", 0));
	i = -1;
	while (++i < ph_n && data->start_time != -1)
	{
		data->philos[i].start_time = ttime;
		pthread_mutex_lock(&data->mutex_lmeal);
		data->philos[i].tlast_meal = ttime;
		pthread_mutex_unlock(&data->mutex_lmeal);
		if (pthread_create(&data->philos[i].thrd, NULL, simple_routine, &data->philos[i]) == -1)
			return (clean_data(data, i), 0);
	}
	if (data->start_time != -1)
	{
		if (pthread_create(&data->death_tracer, NULL, tracer_routine, data) == -1)
			clean_data(data, i);
		data->is_thrd_tracer = 1;
		//if (pthread_create(&data->death_tracer, NULL, waiter_routine, data) == -1)
		//	clean_data(data, i);
	}
	return (1);
}
