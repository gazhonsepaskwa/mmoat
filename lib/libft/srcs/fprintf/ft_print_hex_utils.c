/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:32:29 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/05 08:33:09 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	get_hexsizer(int len, t_flags flags)
{
	if (flags.precision <= len && flags.zero == 1)
		return (flags.width);
	if (flags.precision <= len && flags.zero == 0)
		return (len);
	if (flags.precision >= len)
	{
		if (flags.hash == 1)
			return (flags.precision + 2);
		return (flags.precision);
	}
	return (len);
}

static int	get_hexsizel(int len, t_flags flags)
{
	if (flags.precision <= len)
		return (len);
	if (flags.precision >= len)
	{
		if (flags.hash == 1)
			return (flags.precision + 2);
		return (flags.precision);
	}
	return (len);
}

int	get_hexsize(unsigned int nbr, int len, t_flags flags)
{
	if (flags.precision == 0 && nbr == 0)
		return (0);
	if (flags.precision > len)
		len = flags.precision;
	if (flags.hash == 1 && nbr != 0)
		len += 2;
	if (flags.precision != -1 && len >= flags.precision)
		return (len);
	if (len > flags.width && len >= flags.precision)
		return (len);
	else
	{
		if (flags.left == 1)
			len = get_hexsizel(len, flags);
		if (flags.left == 0)
			len = get_hexsizer(len, flags);
	}
	return (len);
}

static void	puthexnbr_str(char *str, unsigned long nbr, int *i, char *base)
{
	if (nbr > 15)
	{
		puthexnbr_str(str, nbr / 16, i, base);
		puthexnbr_str(str, nbr % 16, i, base);
	}
	else
	{
		str[*i] = base[nbr];
		*i += 1;
	}
}

char	*build_hexn(unsigned int nbr, char *hash, t_flags flags, char *base)
{
	int		i;
	int		len;
	int		tmp;
	char	*strn;

	tmp = hex_len(nbr);
	len = get_hexsize(nbr, tmp, flags);
	strn = malloc(len + 1);
	if (!strn)
		return (NULL);
	strn[len] = '\0';
	if (len == 0)
		return (strn);
	i = 0;
	if (flags.hash == 1 && nbr != 0)
		hex_hash(strn, hash, &i);
	if (flags.hash == 1 && flags.precision < tmp && nbr != 0)
		tmp += 2;
	if (flags.precision == -1 && flags.zero == 1)
		flags.precision = flags.width;
	while (flags.precision-- > tmp)
		strn[i++] = '0';
	puthexnbr_str(strn, nbr, &i, base);
	strn[i] = '\0';
	return (strn);
}
