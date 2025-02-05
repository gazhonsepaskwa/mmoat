/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subsh.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:51:27 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/05 07:51:27 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_node	*remove_parentheses(t_node *lst)
{
	t_node	*it;
	t_node	*out;

	out = NULL;
	it = lst;
	if (it->pressision == SUBSH_S)
		it = it->next;
	while (it->pressision != SUBSH_E)
	{
		add_node_back(&out, ft_strdup(it->val), it->token, it->pressision);
		it = it->next;
	}
	return (out);
}

void create_subsh(t_ast_n *parent, t_node *lst, t_msh *msh)
{
	t_node	*cpy;
	t_node	*cutted;

	cutted = remove_parentheses(lst);
	parent->left = create_ast_n(cutted, parent, msh);
}
