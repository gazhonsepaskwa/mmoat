/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:39:28 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/05 14:39:28 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_redirs(t_ast_n *node)
{
	free(node->redir);
	if (node->files)
		free_tab(node->files);
	free_tab(node->args);
}

void	free_ast(t_ast_n *node)
{
	int i;

	if (node->state == _AND || node->state == _OR)
	{
		free_ast(node->left);
		free_ast(node->right);
	}
	else if (node->state == _PLINE)
	{
		i = -1;
		while (node->pline[++i])
			free_ast(node->pline[i]);
	}
	else if (node->state == _SUBSH)
	{
		free_ast(node->left);
		free_redirs(node);
	}
	else
	{
		free(node->cmd);
		free_redirs(node);
	}

	free(node);
}
