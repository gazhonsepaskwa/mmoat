/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:28 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:57:21 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_redirs(t_ast_n *node)
{
	free(node->redir);
	if (node->files)
		free_tab(node->files);
}

static void	free_cmd(t_ast_n *node)
{
	free(node->cmd);
	free_redirs(node);
	free_tab(node->args);
}

static void	free_pline(t_ast_n *node)
{
	int	i;

	i = -1;
	while (node->pline[++i])
		free_ast(node->pline[i]);
}

void	free_ast(t_ast_n *node)
{
	if (node->state == _AND || node->state == _OR)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	else if (node->state == _SUBSH)
	{
		free_ast(node->left);
		free_redirs(node);
	}
	else if (node->state == _PLINE)
		free_pline(node);
	else
		free_cmd(node);
	free(node);
}

void	free_child(t_msh *msh)
{
	free_ast(msh->head);
	free_msh(msh);
}
