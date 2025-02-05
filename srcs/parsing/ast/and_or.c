/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:57:33 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/05 07:57:33 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_and_or(t_ast_n *parrent, t_node *lst, t_node *token, t_msh *msh)
{
	t_nodell *nodell;

	nodell = cutll(lst, token, 1);
	parrent->left = create_ast_n(nodell->node, parrent, msh);
	parrent->right = create_ast_n(nodell->next->node, parrent, msh);
	// free_lltab(sublsts);
}
