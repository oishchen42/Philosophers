/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:29:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 15:25:34 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	e_msg(t_philo *philo, char *msg, int exit_status)
{
	pthread_mutex_lock(&philo->data->mutex_msg);
	pthread_mutex_lock(&philo->data->mutex_prog_finish);
	philo->data->is_prog_finish = 1;
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	pthread_mutex_unlock(&philo->data->mutex_prog_finish);
	pthread_mutex_unlock(&philo->data->mutex_msg);
	return (exit_status);
}

int	non_thrd_er(char *msg, int exit_status)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	return (exit_status);
}
