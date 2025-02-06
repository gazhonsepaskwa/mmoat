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
	int		deepness;

	out = NULL;
	it = lst;
	it = it->next;
	deepness = 1;
	while (1)
	{
		if (it->pressision == SUBSH_S)
			deepness += 1;
		if (it->pressision == SUBSH_E)
			deepness -= 1;
		if (deepness == 0)
			break;
		add_node_back(&out, ft_strdup(it->val), it->token, it->pressision);
		it = it->next;
	}
	return (out);
}

void create_subsh(t_ast_n *self, t_node *lst, t_msh *msh)
{
	t_node	*cutted;

  self->sh = true;
	cutted = remove_parentheses(lst);
	self->left = create_ast_n(cutted, self, msh, self->sh);
	self->files = NULL;
	self->redir = ft_calloc(1, sizeof(t_redir));
	self->redir[0] = _NR; 
	create_redir_subsh(lst, self);
  // debug
  int i = -1;
	ft_debug("==== SUBSH REDIR\n");
  while (self->redir[++i])
    ft_debug("subsh_redir : [%d]%s\n", self->redir[i], self->files[i]);
	ft_debug("==== SUBSH DONE\n\n");

	// free(cutted);
}
