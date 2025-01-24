/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:53:00 by lderidde          #+#    #+#             */
/*   Updated: 2024/11/04 13:45:38 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

static int	ft_print_arg(char c, va_list args, t_flags flags, int *check)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_print_char(va_arg(args, int), flags);
	else if (c == 's')
		count = ft_print_s(va_arg(args, char *), flags);
	else if (c == 'p')
		count = ft_print_ptr((unsigned long)va_arg(args, void *), flags);
	else if (c == 'd' || c == 'i')
		count = ft_print_int(va_arg(args, int), flags);
	else if (c == 'u')
		count = ft_print_us(va_arg(args, unsigned int), flags);
	else if (c == 'x')
		count = ft_print_hex((unsigned int)va_arg(args, int), 0, flags);
	else if (c == 'X')
		count = ft_print_hex((unsigned int)va_arg(args, int), 1, flags);
	else if (c == '%')
		count = ft_print_char('%', flags);
	if (count == -1)
		*check = -1;
	return (count);
}

static int	parse_flag(const char *str, int i, t_flags *flags)
{
	while (str[++i] && ft_isflag(str[i]))
	{
		if (str[i] == '-')
			*flags = flag_left(*flags);
		if (str[i] == '0' && flags->left == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = flag_precision(str, i, flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] > '0' && str[i] <= '9')
			i = flag_width(str, i, flags) - 1;
		if (is_spec(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}

static int	parse_print(int fd, const char *str, va_list args)
{
	int		count;
	int		i;
	int		tmp;
	t_flags	flags;

	i = -1;
	count = 0;
	tmp = 0;
	while (str[++i])
	{
		flags = init_flags(flags, fd);
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			tmp = parse_flag(str, i, &flags);
			if (flags.spec != 0)
				i = tmp;
			if (str[i] && is_spec(str[i]) && flags.spec != 0)
				count += ft_print_arg(str[i], args, flags, &tmp);
		}
		else if (str[i] != '%')
			count += print_c((unsigned char)str[i], &tmp, flags);
		if (tmp == -1)
			return (-1);
	}
	return (count);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	count = parse_print(fd, str, args);
	va_end(args);
	return (count);
}
