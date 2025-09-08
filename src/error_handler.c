/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:29:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/07 15:02:39 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	e_msg(char *msg, int exit_status) //b_evo not locked as should
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	return (exit_status);
}