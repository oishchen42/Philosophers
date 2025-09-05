/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:14:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/09/05 15:28:32 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosopher.h>

char	*skip_spaces(char *str)
{
	while (*str && (*str >= 9 && str <= 13 || *str == 32))
		str++;
	return (str)
}

int	p_atoi(const char *arg_in_msec)
{
	char	*str;
	int		sign;

	str = arg_in_msec;
	while (*str)
	{
		str = skip_spaces(str);
		if (!(*str))
			return (-1);
	}
}

int	init_args(t_main_struct *data, char **av)
{
	// inits all mallocs
}

int	init_data(t_main_struct *data, int ac, char **av)
{
	if (!(ac <= 5 && ac >= 4))
		return (E_FAIL);
	data->ph_n = p_atoi(av[1]);
	if (!data->ph_n)
		return (E_FAIL);
	data->ttdie_msec = p_atoi(av[2]);
	data->tteat_msec = p_atoi(av[3]);
	data->ttsleep_msec = p_atoi(av[4]);
}

int	main(int ac, char **av)
{
	t_main_struct	data;
	init_data(&data, ac, av);
}