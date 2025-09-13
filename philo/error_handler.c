/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:29:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/09 18:20:30 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	e_msg(t_philo *philo, char *msg, int exit_status)
{
	pthread_mutex_lock(&philo->data->msg_mutex);
	philo->data->is_stop_exec = 1;
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	pthread_mutex_unlock(&philo->data->msg_mutex);
	return (exit_status);
}

int	non_thrd_er(char *msg, int exit_status)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	return (exit_status);
}
