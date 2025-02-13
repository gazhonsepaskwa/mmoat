/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:57:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent, t_msh *msh, bool subsh)
{
	t_ast_n	*node;
	t_node	*token;

	node = malloc(sizeof(t_ast_n));
	token = get_top_token(lst, &node->state);
	node->left = NULL;
	node->right = NULL;
	node->pline = NULL;
	node->msh = msh;
	node->parent = parent;
	node->_stdout = 1;
	node->_stdin = 0;
	node->save_stdo = -1;
	node->save_stdi = -1;
	node->sh = subsh;
	if (node->state == _AND || node->state == _OR)
		create_and_or(node, lst, token, msh);
	else if (node->state == _SUBSH)
		create_subsh(node, lst, msh);
	else if (node->state == _PLINE)
		create_pline(node, lst, token, msh);
	else
		create_cmd(node, lst);
	return (node);
}

t_ast_n	*get_ast(t_msh *msh, t_node *lst)
{
	t_ast_n	*head;

	head = create_ast_n(lst, NULL, msh, false);
	return (head);
}
