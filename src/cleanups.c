/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanups.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:59:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/06 21:27:34 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_mallocs_forks(t_philo_struct *data, int fork_pos, int is_mtx_msg, int is_mtx_odd)
{
	if (fork_pos)
	{
		while (--fork_pos >= 0)
			pthread_mutex_destroy(&data->forks[fork_pos]);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (is_mtx_msg)
		pthread_mutex_destroy(data->msg_mutex);
	if (is_mtx_odd)
		pthread_mutex_destroy(data->odd_mutex);
}


//void	inti_clean_data(t_philo_struct *data)
//{
//	int	i;

//	i = -1;
//	if (data->philos)
//		free(data->philos);
//	if ()
//}