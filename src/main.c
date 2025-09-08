/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:14:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/07 18:46:42 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	init_args(t_philo_struct *data, char **av)
//{
//	// inits all mallocs
//}

void	join_threads(t_philo_struct *data)
{
	int	i;

	i = 0;
	while (i < data->ph_n)
	{
		pthread_join(data->philos[i].thrd, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo_struct	data;

	if (write(STDIN_FILENO, "", 0) == -1)
		return (e_msg("STDIN_FILENO is closed", 1));
	if (!init_data(&data, ac, av))
		return (1);
	if (!start_prog(&data))
		return (1);
	join_threads(&data);
	//clean_data(&data);
	return (0);
}
