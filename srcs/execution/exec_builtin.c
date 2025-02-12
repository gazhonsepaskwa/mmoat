/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:48:21 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:06 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "exit", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "env", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "export", -1) == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_ast_n *node)
{
	int	ret;

	expand_node(node);
	if (ft_strncmp(node->cmd, "exit", -1) == 0)
		ret = builtin_exit(node->args, node->sh, node);
	else if (ft_strncmp(node->cmd, "pwd", -1) == 0)
		ret = builtin_pwd(node->args);
	else if (ft_strncmp(node->cmd, "echo", -1) == 0)
		ret = builtin_echo(node, node->msh->env);
	else if (ft_strncmp(node->cmd, "env", -1) == 0)
		ret = builtin_env(node->args, node->msh->env);
	else if (ft_strncmp(node->cmd, "unset", -1) == 0)
		ret = builtin_unset(node->args, node);
	else if (ft_strncmp(node->cmd, "cd", -1) == 0)
		ret = builtin_cd(node->args, node);
	else
		ret = builtin_export(node->args, node);
	return (ret);
}
