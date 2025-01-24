/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:28:26 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 13:35:23 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int	print_c(unsigned char c, int *check, t_flags flags)
{
	int	tmp;

	tmp = write (flags.fd, &c, 1);
	if (tmp < 1)
	{
		*check = -1;
		return (-1);
	}
	else
		return (1);
}

int	ft_print_c(unsigned char c, t_flags flags)
{
	int	tmp;

	tmp = write (flags.fd, &c, 1);
	if (tmp < 1)
		return (-1);
	else
		return (1);
}

int	ft_print_char(unsigned char c, t_flags flags)
{
	int	count;
	int	check;

	check = 0;
	count = 0;
	if (flags.left == 1)
		check = ft_print_c(c, flags);
	if (check == -1)
		return (-1);
	count += check;
	if (flags.zero == 1)
		count += ft_print_width(flags, 1, 1, &check);
	else if (flags.zero == 0)
		count += ft_print_width(flags, 1, 0, &check);
	if (flags.left == 0 && check != -1)
	{
		check = ft_print_c(c, flags);
		if (check == -1)
			return (-1);
		else
			count += check;
	}
	if (check == -1)
		return (-1);
	return (count);
}
