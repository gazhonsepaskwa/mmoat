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

static void	remove_parentheses(t_node **lst)
{
    t_node *tmp;
    t_node *cpy;

    if (!lst || !*lst || !(*lst)->next)
        return;

    tmp = *lst;
    *lst = (*lst)->next;
    free(tmp->val);
    free(tmp);
    cpy = *lst;
    while (cpy->next && cpy->next->next)
        cpy = cpy->next;
    if (cpy->next)
    {
        free(cpy->next->val);
        free(cpy->next);
        cpy->next = NULL;
    }
}

void create_subsh(t_ast_n *parent, t_node *lst, t_msh *msh)
{
	t_node *cpy;

	cpy = lst;
	while (cpy)
	{
		ft_printf("%s\n", cpy->val);
		cpy = cpy->next;
	}
	remove_parentheses(&lst);
	ft_printf("\n\n");
	cpy = lst;
	while (cpy)
	{
		ft_printf("%s\n", cpy->val);
		cpy = cpy->next;
	}
	parent->left = create_ast_n(lst, parent, msh);
}
