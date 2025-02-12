/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:31:56 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:35 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_silent(char *str)
{
	int		i;
	bool	flag;

	i = 0;
	flag = false;
	if (str[i] && str[i] != '-')
		return (flag);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		flag = true;
	return (flag);
}

char	*ft_getenv(char *str, char **envp)
{
	char	*tmp;
	int		j;
	size_t	len;

	j = 0;
	tmp = ft_strjoin(str, "=");
	len = ft_strlen(tmp);
	while (envp[j] && ft_strnstr(envp[j], tmp, len) == NULL)
		j++;
	if (!envp[j])
		return (free(tmp), NULL);
	free(tmp);
	return (&envp[j][len]);
}

int	print_exit(char **arg, t_ast_n *node)
{
	if (*arg && ft_strncmp(*arg, "$?", 2) == 0)
	{
		ft_fprintf(1, "%d", node->msh->ex_code);
		return (1);
	}
	return (0);
}

static void	echo_print(t_ast_n *node, int j, char **envp)
{
	int	i;

	(void)envp;
	while (node->args[j])
	{
		i = 0;
		while (node->args[j][i])
		{
			if (print_exit(&node->args[j], node))
				i += 2;
			else
				ft_put_c(node->args[j][i++]);
		}
		j++;
		if (node->args[j])
			ft_put_c(' ');
	}
}

int	builtin_echo(t_ast_n *node, char **envp)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	while (node->args[i] && is_silent(node->args[i]))
	{
		flag = true;
		i++;
	}
	echo_print(node, i, envp);
	if (!flag)
		ft_printf("\n");
	return (0);
}
