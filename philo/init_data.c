/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:08:34 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 21:05:34 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_data_ints(t_philo_struct *data, int ac, char **av)
{
	data->is_death_anounced = 0;
	data->is_thrd_tracer = 0;
	data->is_prog_finish = 0;
	data->ready_mtx_lmeal = 0;
	data->ready_mtx_lmsg = 0;
	data->is_forks_ready = 0;
	data->ready_mtx_msg = 0;
	data->ready_mtx_prog_finish = 0;
	data->eat_needed = INT_MAX;
	data->eat_did = 0;
	data->ph_n = p_atoi(av[1]);
	data->ttdie_msec = p_atoi(av[2]);
	data->tteat_msec = p_atoi(av[3]);
	data->ttsleep_msec = p_atoi(av[4]);
	if (ac == 6)
		data->eat_needed = p_atoi(av[5]);
	if (data->ph_n < 0 || data->ttdie_msec < 0 || data->tteat_msec < 0
		|| data->eat_needed < 0 || data->ttsleep_msec < 0)
		return (0);
	return (1);
}

static int	init_data_mallocs_forks(t_philo_struct *data)
{
	int	i;

	data->philos = malloc((unsigned int)data->ph_n * sizeof(t_philo));
	if (!data->philos)
		return (non_thrd_er("malloc error\n", 0));
	data->forks = malloc(data->ph_n * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (free(data->philos), non_thrd_er("malloc error\n", 0));
	i = -1;
	while (++i < data->ph_n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) == -1)
			return (destroy_forks(data, i), 0);
	}
	data->is_forks_ready = 1;
	return (1);
}

static int	assign_forks(t_philo_struct *data)
{
	int	i;

	i = -1;
	while (++i < data->ph_n)
	{
		if (i != data->ph_n - 1)
		{
			data->philos[i].fork_1 = &data->forks[i];
			data->philos[i].fork_2 = &data->forks[i + 1];
		}
		else
		{
			data->philos[i].fork_1 = &data->forks[0];
			data->philos[i].fork_2 = &data->forks[i];
		}
	}
	return (1);
}

static void	init_philos_ints(t_philo_struct *data)
{
	int	i;
	int	is_odd;

	is_odd = (data->ph_n % 2 == 1);
	i = -1;
	while (++i < data->ph_n)
	{
		data->philos[i].data = data;
		data->philos[i].eat_did = 0;
		data->philos[i].tteat = data->tteat_msec;
		data->philos[i].ttsleep = data->ttsleep_msec;
		data->philos[i].ttdie = data->ttdie_msec;
		data->philos[i].eat_needed = data->eat_needed;
		data->philos[i].id = i + 1;
		data->philos[i].is_wait = (i % 2 == 1);
		data->philos[i].is_odd = is_odd;
		data->philos[i].ph_max = data->ph_n;
		data->philos[i].round = 1;
	}
	if (is_odd)
		data->philos[i - 1].is_wait = 1;
	data->odd_flg = FIRST_PHILO;
}

int	init_data(t_philo_struct *data, int ac, char **av)
{
	if (!(ac == 6 || ac == 5))
		return (non_thrd_er("expected from 4 to 5 variables\n", 0));
	if (!init_data_ints(data, ac, av))
		return (non_thrd_er("no negative values pls\n", 0));
	if (!init_data_mallocs_forks(data) || !init_other_mtxs(data))
		return (non_thrd_er("init_data_mallocs_forks failed\n", 0));
	init_philos_ints(data);
	assign_forks(data);
	return (1);
}
