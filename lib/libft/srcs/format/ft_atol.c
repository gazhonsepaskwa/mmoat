/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:40:16 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 15:40:16 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	is_signed(char c, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		return (1);
	}
	return (0);
}

long	ft_atol(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	errno = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	if (is_signed(*str, &sign))
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (((sign > 0) && res >= (LONG_MAX / 10)
				&& (*str - '0' > LONG_MAX % 10))
			|| (sign == -1 && res >= LONG_MAX / 10
				&& *str - '0' > LONG_MAX % 10 + 1))
		{
			errno = ERANGE;
			break ;
		}
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * sign);
}
