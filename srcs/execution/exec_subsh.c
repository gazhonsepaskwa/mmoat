/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subsh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:52:04 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:30:47 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_shcmd(t_ast_n *node)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_builtin(node->cmd))
		return (exec_builtin(node));
	else
	{
		pid = fork();
		if (pid == 0)
			exec(node);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else
				return (1);
		}
		else
			perror("fork");
		return (1);
	}
}

static int	execute_shand(t_ast_n *node)
{
	node->msh->ex_code = execute_shcommand(node->left);
	if (node->msh->ex_code == 0)
		node->msh->ex_code = execute_shcommand(node->right);
	return (node->msh->ex_code);
}

int	execute_shcommand(t_ast_n *node)
{
	if (node->state == _CMD)
		if (handle_redir(node) == 1)
			return (1);
	if (node->state == _CMD)
		node->msh->ex_code = exec_shcmd(node);
	else if (node->state == _AND)
		execute_shand(node);
	else if (node->state == _OR)
	{
		node->msh->ex_code = execute_shcommand(node->left);
		if (node->msh->ex_code != 0)
			node->msh->ex_code = execute_shcommand(node->right);
	}
	else if (node->state == _PLINE)
		node->msh->ex_code = exec_pline(node->pline);
	else if (node->state == _SUBSH)
		node->msh->ex_code = exec_subsh(node->left);
	if (node->state == _CMD)
		reset_redir(node);
	if (node->state == _CMD)
		set_var_env("_", node->args[count_args(node->args) - 1], node->msh);
	return (node->msh->ex_code);
}

static int	in_subsh(t_ast_n *node)
{
	int	ret;

	if (handle_redir(node->parent) == 1)
	{
		free_child(node->msh);
		return (1);
	}
	ret = execute_shcommand(node);
	free_child(node->msh);
	return (ret);
}

int	exec_subsh(t_ast_n *node)
{
	int		status;
	pid_t	pid;
	int		ret;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		ret = in_subsh(node);
		exit (ret);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && node->parent->state != _PLINE)
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}
