/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:14:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 15:25:47 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_philo_struct	data;

	if (write(STDIN_FILENO, "", 0) == -1)
		return (non_thrd_er("STDIN_FILENO is closed", 1));
	if (write(STDERR_FILENO, "", 0) == -1)
		return (non_thrd_er("STDERR_FILENO is closed", 1));
	if (!init_data(&data, ac, av))
		return (1);
	if (!start_prog(&data))
		return (non_thrd_er("pthread_create failed\n", 1));
	clean_data(&data, data.ph_n);
	return (0);
}
