/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:32:13 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/06 13:27:33 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	err_msg_cmd("exit", arg, "numeric argument required", 2);
	exit(2);
}

int	bash_exiterrorcount(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (2);
}

int	builtin_exit(char **arg, bool depth, t_ast_n *node)
{
	long	res;

	res = node->msh->ex_code;
	if (arg[1] && ft_isnumeric(arg[1]))
		res = ft_atol(arg[1]);
	if (depth == true)
	{
		if (count_args(arg) > 2 && ft_isnumeric(arg[1]))
			return (err_msg_cmd("exit", NULL, "too many arguments", 1));
		else if (arg[1] && (!ft_isnumeric(arg[1]) || errno == ERANGE))
			exit (err_msg_cmd("exit", arg[1], "numeric argument required", 2));
		exit (res % 256);
	}
	if (count_args(arg) > 2 && ft_isnumeric(arg[1]))
		return (bash_exiterrorcount());
	else if (arg[1] && (!ft_isnumeric(arg[1]) || errno == ERANGE))
		bash_exit_errornum(arg[1]);
	else
		bash_exit(res % 256);
	return (1);
}
