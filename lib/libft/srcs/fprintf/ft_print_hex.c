/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:15:38 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/05 08:32:57 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	hex_hash(char *s, char *hash, int *i)
{
	s[0] = hash[0];
	s[1] = hash[1];
	*i = 2;
	return ;
}

static int	display_hexnum(char *str, int *check, t_flags flags)
{
	int	count;
	int	len;

	len = ft_strlen(str);
	count = 0;
	count = write(flags.fd, str, len);
	if (count < len)
		*check = -1;
	return (count);
}

static int	pnbr_base(unsigned long num, char *base, char *hash, t_flags flags)
{
	int		count;
	char	*strn;
	int		check;
	int		len;

	count = 0;
	check = 0;
	len = hex_len(num);
	len = get_hexsize(num, len, flags);
	strn = build_hexn(num, hash, flags, base);
	if (!strn)
		return (-1);
	if (flags.left == 1)
		count = display_hexnum(strn, &check, flags);
	count += ft_print_width(flags, len, 0, &check);
	if (flags.left == 0)
		count += display_hexnum(strn, &check, flags);
	free(strn);
	if (check == -1)
		return (-1);
	else
		return (count);
}

int	ft_print_hex(unsigned int num, int uppercase, t_flags flags)
{
	int				count;
	unsigned long	nbr;

	nbr = num;
	count = 0;
	if (uppercase)
		count = pnbr_base(nbr, "0123456789ABCDEF", "0X", flags);
	else
		count = pnbr_base(nbr, "0123456789abcdef", "0x", flags);
	return (count);
}
