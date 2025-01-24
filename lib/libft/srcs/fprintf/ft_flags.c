/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:28 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 13:45:40 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

t_flags	init_flags(t_flags flags, int fd)
{
	flags.spec = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.left = 0;
	flags.zero = 0;
	flags.hash = 0;
	flags.plus = 0;
	flags.space = 0;
	flags.fd = fd;
	return (flags);
}

t_flags	flag_left(t_flags flags)
{
	flags.left = 1;
	flags.zero = 0;
	return (flags);
}

int	flag_precision(const char *str, int i, t_flags *flags)
{
	int	j;
	int	res;

	res = 0;
	j = i + 1;
	while (str[j] >= '0' && str[j] <= '9')
	{
		res = (res * 10) + str[j] - '0';
		j++;
	}
	flags->precision = res;
	return (j);
}

int	flag_width(const char *str, int i, t_flags *flags)
{
	int	res;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + str[i] - '0';
		i++;
	}
	flags->width = res;
	return (i);
}

int	ft_print_width(t_flags flags, int size, int zero, int *check)
{
	int	count;
	int	tmp;
	int	width;

	width = flags.width;
	count = 0;
	while (width - size > 0)
	{
		if (zero == 1)
			tmp = ft_print_c('0', flags);
		else
			tmp = ft_print_c(' ', flags);
		if (tmp == -1)
		{
			*check = -1;
			return (-1);
		}
		count += tmp;
		width--;
	}
	return (count);
}
