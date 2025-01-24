/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_us_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:14:47 by lderidde          #+#    #+#             */
/*   Updated: 2024/10/31 15:03:30 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	get_ussizer(int len, t_flags flags)
{
	if (flags.precision < len && flags.zero == 1)
		return (flags.width);
	if (flags.precision < len && flags.zero == 0)
		return (len);
	if (flags.precision > len)
		return (flags.precision);
	return (len);
}

static int	get_ussizel(int len, t_flags flags)
{
	if (flags.precision < len)
		return (len);
	if (flags.precision > len)
		return (flags.precision);
	return (len);
}

int	get_ussize(unsigned int num, int len, t_flags flags)
{
	if (flags.precision == 0 && num == 0)
		return (0);
	if (flags.precision != -1 && len > flags.precision)
		return (len);
	if (len > flags.width && len > flags.precision)
		return (len);
	else
	{
		if (flags.left == 1)
			len = get_ussizel(len, flags);
		if (flags.left == 0)
			len = get_ussizer(len, flags);
	}
	return (len);
}

static	void	putusnbr_str(char *str, unsigned int nbr, int *i, int len)
{
	if (nbr > 9)
	{
		putusnbr_str(str, nbr % 10, i, len);
		putusnbr_str(str, nbr / 10, i, len);
	}
	else
	{
		str[len - 1 - *i] = nbr + '0';
		*i += 1;
	}
}

char	*build_strusn(char *str, unsigned int nbr, int len)
{
	int	i;

	i = 0;
	if (len - i == 0)
		return (str);
	putusnbr_str(str, nbr, &i, len);
	if (len - i == 0)
		return (str);
	while (len - i - 1 > 0)
		str[len - i++ - 1] = '0';
	str[0] = '0';
	return (str);
}
