/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:34:35 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/16 15:25:49 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	char	*cpy_str;

	cpy_str = (char *)str;
	while (*cpy_str)
		cpy_str++;
	return (cpy_str - str);
}

static char	*skip_spaces(char *str)
{
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	return (str);
}

static int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

int	p_atoi(char *str)
{
	long	res;

	res = 0;
	str = skip_spaces(str);
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				return (-1);
			str++;
		}
		while (*str && is_num(*str))
		{
			res = res * 10 + (*str - '0');
			str++;
		}
		if (*str)
			return (non_thrd_er("unallowed sign detected\n", -1));
		if (res > INT_MAX || res < INT_MIN)
			return (non_thrd_er("one of the vars overalps intiger limits\n",
					-1));
		return ((int)res);
	}
	return (non_thrd_er("detected unallowed value\n", -1));
}
