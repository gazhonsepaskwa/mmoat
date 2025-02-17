/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:22:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 11:14:14 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_and(t_ast_n *node)
{
	node->msh->ex_code = execute_command(node->left);
	if (node->msh->ex_code == 0)
		node->msh->ex_code = execute_command(node->right);
	return (node->msh->ex_code);
}

int	execute_command(t_ast_n *node)
{
	if (!node || (node->state == _CMD && node->cmd == NULL))
		return (0);
	if (node->state == _CMD)
		if (handle_redir(node))
			return (1);
	if (node->state == _CMD)
		node->msh->ex_code = exec_scmd(node);
	else if (node->state == _AND)
		node->msh->ex_code = execute_and(node);
	else if (node->state == _OR)
	{
		node->msh->ex_code = execute_command(node->left);
		if (node->msh->ex_code != 0)
			node->msh->ex_code = execute_command(node->right);
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
