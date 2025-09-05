/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:14:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 17:41:28 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	init_args(t_philo_struct *data, char **av)
//{
//	// inits all mallocs
//}

int	init_data(t_philo_struct *data, int ac, char **av)
{ // b_evo look for division of the function
	if (!(ac == 6 || ac == 5))
		return (e_msg("expected from 4 to 5 variables\n", 1));
	data->eat_needed = INT_MAX;
	data->eat_did = 0;
	data->ph_n = p_atoi(av[1]);
	if (!data->ph_n)
		return (E_FAIL);
	data->ttdie_msec = p_atoi(av[2]);
	data->tteat_msec = p_atoi(av[3]);
	data->ttsleep_msec = p_atoi(av[4]);
	if (ac == 6)
		data->eat_needed = p_atoi(av[5]);
	if (data->ph_n < 0 || data->ttdie_msec < 0 || data->tteat_msec < 0
		|| data->eat_needed < 0 || data->ttsleep_msec < 0)
		return (e_msg("No negative value allowed\n", 1));
	data->philos = malloc((unsigned int)data->ph_n * sizeof(pthread_t));
	if (!data->philos)
		return (e_msg("malloc error\n", 0));
	data->forks = malloc((unsigned int)data->ph_n * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (free(data->philos), e_msg("malloc error\n", 0));
	data->death_tracer = malloc(sizeof(pthread_t));
	if (!data->death_tracer)
		return (free(data->philos), free(data->forks), e_msg("malloc error\n", 0));
	return (1);
}

int	main(int ac, char **av)
{
	t_philo_struct	data;

	init_data(&data, ac, av);
	start_prog(&data);
	clean_data(&data);
	return (0);
}