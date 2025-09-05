/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:34:35 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 15:53:08 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t	ft_strlen(const char *str)
{
	char	*cpy_str;

	cpy_str = str;
	while (*cpy_str)
		cpy_str++;
	return (cpy_str - str);
}

static char	*skip_spaces(char *str)
{
	while (*str && (*str >= 9 && str <= 13 || *str == 32))
		str++;
	return (str);
}

static int	is_num(char *str)
{
	return (*str >= '0' && *str <= '9');
}

int	p_atoi(const char *arg_in_msec)
{
	char	*str;
	int		sign;
	int		res;

	str = arg_in_msec;
	sign = 1;
	res = 0;
	while (*str)
	{
		str = skip_spaces(str);
		if (!(*str))
			return (error_msg_exit_status("type smth apart from spaces\n", 1));
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign = -1;
			str++;
		}
		while (*str && is_num(*str))
			res = res * 10 + (*str - '0');
		str++;
	}
	if (*str)
		return (error_msg_exit_status("unallowed sign detected\n", 1));
	return (res * sign);
}
