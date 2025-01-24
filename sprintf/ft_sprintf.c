/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:46:45 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/24 13:46:45 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sprintf.h"

static int	is_spec(char c)
{
	if (c == 'c' || c == 's' || c == 'd')
		return (1);
	return (0);
}

static char	*add_arg(char c, char *str, va_list args)
{
	if (c == 'c')
		return (ft_strfjoinc(str, va_arg(args, int)));
	else if (c == 's')
		return (ft_strfjoin(str, va_arg(args, char *)));
	else if (c == 'd')
		return (ft_strfjoind(str, ft_itoa(va_arg(args, int))));
}

static char	*build_str(const char *str, va_list args)
{
	char	*out;
	int		i;

	out = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			if (is_spec(str[++i]))
				out = add_arg(str[i], out, args);
			else
				out = ft_strfjoinc(out, '%');
		}
		else
			out = ft_strfjoinc(out, str[i]);
		i++;
	}
	return (out);
}

char	*ft_sprintf(const char *str, ...)
{
	va_list	args;
	char	*out;

	va_start(args, str);
	out = build_str(str, args);
	va_end(args);
	return (out);
}
