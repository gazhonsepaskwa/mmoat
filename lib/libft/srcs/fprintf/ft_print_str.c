/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:00:06 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 08:42:43 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	print_string(char *str, t_flags flags, int *check)
{
	int	count;
	int	i;
	int	tmp;

	tmp = 0;
	i = 0;
	count = 0;
	if (flags.precision == -1)
		flags.precision = ft_strlen(str);
	while (str[i] && i < flags.precision)
	{
		tmp = ft_print_c(str[i], flags);
		if (tmp == -1)
		{
			*check = -1;
			return (-1);
		}
		count += tmp;
		i++;
	}
	return (count);
}

int	ft_print_s(char *str, t_flags flags)
{
	int	count;
	int	check;
	int	len;

	check = 0;
	count = 0;
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.precision > 0 && flags.precision > len)
		flags.precision = len;
	if (flags.left == 1)
		count += print_string(str, flags, &check);
	if (flags.precision >= 0)
		count += ft_print_width(flags, flags.precision, 0, &check);
	else
		count += ft_print_width(flags, len, 0, &check);
	if (flags.left == 0)
		count += print_string(str, flags, &check);
	if (check == -1)
		return (-1);
	return (count);
}
