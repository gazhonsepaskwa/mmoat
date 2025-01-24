/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:10:55 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/05 08:38:38 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static void	print_p(unsigned long add, int *count, int *check, t_flags flags)
{
	int	tmp;

	if (add >= 16)
	{
		print_p(add / 16, *(&count), *(&check), flags);
		print_p(add % 16, *(&count), *(&check), flags);
	}
	else
	{
		if (add < 10)
			tmp = ft_print_c(add + '0', flags);
		else
			tmp = ft_print_c((add - 10) + 'a', flags);
		if (tmp == -1)
		{
			*check = -1;
			return ;
		}
		*count += 1;
	}
}

static int	ft_print_p(unsigned long add, int *check2, t_flags flags)
{
	int	count;
	int	check;

	check = 0;
	count = 0;
	count += ft_fprintf(flags.fd, "0x");
	if (count == -1)
		return (-1);
	print_p(add, &count, &check, flags);
	if (check == -1)
	{
		*check2 = -1;
		return (-1);
	}
	else
		return (count);
}

int	ft_print_ptr(unsigned long add, t_flags flags)
{
	int	count;
	int	check;

	check = 0;
	count = 0;
	if (flags.left == 1)
		count += ft_print_p(add, &check, flags);
	if (flags.width != 0)
	{
		if (add == 0)
			count += ft_print_width(flags, 3, 0, &check);
		else
			count += ft_print_width(flags, hex_len(add) + 2, 0, &check);
	}
	if (flags.left == 0)
		count += ft_print_p(add, &check, flags);
	if (check == -1)
		return (-1);
	count += check;
	return (count);
}
