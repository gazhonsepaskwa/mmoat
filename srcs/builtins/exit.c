/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:13 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/24 14:32:13 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	bash_exit(int code)
{
	ft_putendl_fd("exit", 2);
	exit(code);
}

void	bash_exit_errornum(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_put_s_fd("minishell: exit: ", 2);
	write(2, arg, ft_strlen(arg));
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

static	char	*get_arg(char *str)
{
	int		i;

	i = 4;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] == ' ')
		i++;
	return (&str[i]);
}

int	is_sep(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int	count_arg(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] && str[i + 1])
	{
		if (!is_sep(str[i]) && is_sep(str[i + 1]))
			count++;
		i++;
	}
	return (count);
}

void	bash_exiterrorcount(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	/*
	 * SET EXIT CODE WITHOUT EXITING MINISHELL
	 */
}

void	builtin_exit(char *str, bool depth)
{
	char 	*arg;

	arg = get_arg(str);
	long res = ft_atol(arg);
	(void)res;
	if (errno == ERANGE)
		ft_printf("error numeric aarg\n");
	if (depth == true)
	{
		if (count_arg(str) >= 2)
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			exit (1);
		}
		if (!ft_isnumeric(arg))
		{
			ft_put_s_fd("minishell: exit: ", 2);
			write(2, arg, ft_strlen(arg));
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		exit(ft_atoi(arg) % 256);
	}
	if (count_arg(str) >= 2)
		bash_exiterrorcount();
	else if (ft_isnumeric(arg))
		bash_exit(ft_atoi(arg) % 256);
	else
		bash_exit_errornum(arg);
}
