/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subsh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:52:04 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 09:52:04 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/exec.h"

int	exec_shcmd(t_ast_n *node)
{
	pid_t	pid;
	int		status;

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

int	execute_shcommand(t_ast_n *node)
{
	if (node->state == _CMD)
		handle_redir(node);
	if (node->state == _CMD)
		node->msh->ex_code = exec_shcmd(node);
	else if (node->state == _AND)
	{
		node->msh->ex_code = execute_shcommand(node->left);
		if (node->msh->ex_code == 0)
			node->msh->ex_code = execute_shcommand(node->right);
	}
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
	return (node->msh->ex_code);
}

int	exec_subsh(t_ast_n *node)
{
	int		status;
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		handle_redir(node->parent);
		ret = execute_shcommand(node);
		free_child(node->msh);
		exit(ret);
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
