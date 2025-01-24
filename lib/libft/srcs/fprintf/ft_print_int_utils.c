/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:01:33 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 13:33:48 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	get_sizer(int num, int len, t_flags flags)
{
	int	nbr;

	nbr = num;
	if (flags.precision < len && flags.zero == 1)
		return (flags.width);
	if (flags.precision < len && flags.zero == 0)
		return (len);
	if (flags.precision >= len)
	{
		if (((flags.space == 1 || flags.plus == 1) && nbr >= 0) || nbr < 0)
			return (flags.precision + 1);
		else
			return (flags.precision);
	}
	return (len);
}

static int	get_sizel(int num, int len, t_flags flags)
{
	int	nbr;

	nbr = num;
	if (flags.precision < len)
		return (len);
	if (flags.precision >= len)
	{
		if (((flags.space == 1 || flags.plus == 1) && nbr >= 0) || nbr < 0)
			return (flags.precision + 1);
		else
			return (flags.precision);
	}
	return (len);
}

int	get_size(int num, int len, t_flags flags)
{
	if (flags.precision == 0 && num == 0)
	{
		if (flags.plus == 1 || flags.space == 1)
			return (1);
		return (0);
	}
	if ((flags.space == 1 || flags.plus == 1) && num >= 0)
		len += 1;
	if (flags.precision != -1 && len > flags.precision)
		return (len);
	if (len > flags.width && len > flags.precision)
		return (len);
	if (num < 0 && flags.precision == len)
		return (len + 1);
	else
	{
		if (flags.left == 1)
			len = get_sizel(num, len, flags);
		if (flags.left == 0)
			len = get_sizer(num, len, flags);
	}
	return (len);
}

static	void	putnbr_str(char *str, long nbr, int *i, int len)
{
	if (nbr > 9)
	{
		putnbr_str(str, nbr % 10, i, len);
		putnbr_str(str, nbr / 10, i, len);
	}
	else
	{
		str[len - 1 - *i] = nbr + '0';
		*i += 1;
	}
}

char	*build_strn(char *str, long nbr, int len, t_flags flags)
{
	int	i;

	i = 0;
	check_minus(str);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	if (len - i == 0)
		return (str);
	putnbr_str(str, nbr, &i, len);
	if (len - i == 0 && (flags.space == 0 && flags.plus == 0))
		return (str);
	while (len - i - 1 > 0)
		str[len - i++ - 1] = '0';
	if (len - i > 0 && str[len - i -1] == '-')
		return (str);
	if (nbr >= 0 && flags.plus == 1)
		str[0] = '+';
	else if (nbr >= 0 && flags.space == 1)
		str[0] = ' ';
	else
		str[0] = '0';
	return (str);
}
