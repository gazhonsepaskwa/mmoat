/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:57:33 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/07 17:57:01 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	create_and_or(t_ast_n *self, t_node *lst, t_node *token, t_msh *msh)
{
	t_nodell	*nodell;

	nodell = cutll(lst, token, 1);
	self->left = create_ast_n(nodell->node, self, msh, self->sh);
	self->right = create_ast_n(nodell->next->node, self, msh, self->sh);
	free_lltab(nodell);
}
