/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_us.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:38:55 by lderidde          #+#    #+#             */
/*   Updated: 2024/10/31 15:06:23 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static char	*ft_itoa_usnum(unsigned int num, t_flags flags)
{
	int		len;
	char	*str;
	long	nbr;

	nbr = num;
	len = num_len(nbr);
	len = get_ussize(num, len, flags);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	str = build_strusn(str, num, len);
	return (str);
}

static int	display_usint(char *str, int *check, t_flags flags)
{
	int	count;
	int	len;

	len = ft_strlen(str);
	count = 0;
	count = write(flags.fd, str, len);
	if (count < len)
	{
		*check = -1;
		return (-1);
	}
	return (count);
}

int	ft_print_us(unsigned int num, t_flags flags)
{
	int		count;
	char	*strn;
	int		check;

	check = 0;
	count = 0;
	strn = ft_itoa_usnum(num, flags);
	if (!strn)
		return (-1);
	if (flags.left == 1)
		count = display_usint(strn, &check, flags);
	count += ft_print_width(flags, ft_strlen(strn), 0, &check);
	if (flags.left == 0)
		count += display_usint(strn, &check, flags);
	free(strn);
	if (check == -1)
		return (-1);
	else
		return (count);
}
