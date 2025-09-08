/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:34:35 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/08 15:01:48 by oishchen         ###   ########.fr       */
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
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	str = skip_spaces(str);
	while (*str)
	{
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				sign = -1;
			str++;
		}
		while (*str && is_num(*str))
		{
			res = res * 10 + (*str - '0');
			str++;
		}
		if (*str)
			return (e_msg("unallowed sign detected\n", 1));
		if (res > INT_MAX || res < INT_MIN)
			return (e_msg("one of the vars overalps intiger limits\n", -1));
		return ((int)res * sign);
	}
	return (e_msg("detected unallowed value\n", -1));
}
