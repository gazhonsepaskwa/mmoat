/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 07:54:22 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/05 07:54:22 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_pline(t_ast_n *self, t_node *lst, t_node *token, t_msh *msh)
{
	t_nodell	*nodell;
	t_nodell	*cpy;
	int			count;
	int			i;

	nodell = cutll(lst, token, -1);
	cpy = nodell;
	count = 0;
	while (cpy)
	{
		count++;
		cpy = cpy->next;
	}
	self->pline = ft_calloc(count + 1, sizeof(t_ast_n *));
	cpy = nodell;
	i = 0;
	while (cpy)
	{
		self->pline[i] = create_ast_n(cpy->node, self, msh, self->sh);
		cpy = cpy->next;
		i++;
	}
	cpy = NULL;
	// free_lltab(sublsts);
}
