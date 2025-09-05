/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:29:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 15:37:23 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	error_msg_exit_status(char *msg, int exit_status)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	return (exit_status);
}