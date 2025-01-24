/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:04:33 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 13:26:44 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	check_minus(char *str)
{
	if (str[0] == '-')
		str[0] = 'a';
}

static char	*ft_itoa_num(int num, t_flags flags)
{
	int		len;
	char	*str;
	long	nbr;

	nbr = num;
	len = num_len(nbr);
	len = get_size(num, len, flags);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	str = build_strn(str, nbr, len, flags);
	return (str);
}

static int	display_int(char *str, int *check, t_flags flags)
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

int	ft_print_int(int num, t_flags flags)
{
	int		count;
	char	*strn;
	int		check;

	check = 0;
	count = 0;
	strn = ft_itoa_num(num, flags);
	if (!strn)
		return (-1);
	if (flags.left == 1)
		count = display_int(strn, &check, flags);
	count += ft_print_width(flags, ft_strlen(strn), 0, &check);
	if (flags.left == 0)
		count += display_int(strn, &check, flags);
	free(strn);
	if (check == -1)
		return (-1);
	else
		return (count);
}
