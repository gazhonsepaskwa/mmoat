/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/24 08:22:16 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// ===================================================================

t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent);

// ====================================================================


void	create_and_or(t_ast_n *parrent, t_node *lst, t_node *token)
{
	t_nodell *nodell;

	nodell = cutll(lst, token->val, 1);
	parrent->left = create_ast_n(nodell->node, parrent);
	parrent->right = create_ast_n(nodell->next->node, parrent);
	// free_lltab(sublsts);
}



// ===================================================================



t_redir get_red()

void	create_cmd(t_ast_n *self, t_node *lst)
{
	self->state = _CMD;
	self->cmd = ft_strdup(lst->val);
	self->args = ft_split("test random val", " ");
}




//=====================================================================




// void	create_pline(t_ast_n *parent, t_node *lst, t_node *token)
// {
//
// }




//======================================================================



void remove_parentheses(t_node **lst)
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

void create_subsh(t_ast_n *parent, t_node *lst)
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
	parent->left = create_ast_n(lst, parent);
}



//==================================================================



t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent)
{
	t_ast_n *node;
	t_node	*token;

	node = malloc(sizeof(t_ast_n));
	token = get_top_token(lst, &node->state);

	(void)token;
	(void)parent;

	node->left = NULL;
	node->right = NULL;
	node->pline = NULL;
	// node->parent = parent; pas encore tester

	if (node->state == _AND || node->state == _OR)
		create_and_or(node, lst, token);
	else if (node->state == _SUBSH)
		create_subsh(node, lst);
	// if (node->state == _PLINE)
	// 	create_pline(node, lst, token);
	else
		create_cmd(node, lst);

	return (node);
}

t_ast_n	*get_ast(char **envp, t_node *lst)
{
	t_ast_n *head;
	(void)envp;

	head = create_ast_n(lst, NULL);
	return (head);
}
