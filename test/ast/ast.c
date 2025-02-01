/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/01 11:13:58 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// ===================================================================

t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent);

// ====================================================================


void	create_and_or(t_ast_n *parrent, t_node *lst, t_node *token)
{
	t_nodell *nodell;

	nodell = cutll(lst, token, 1);
	parrent->left = create_ast_n(nodell->node, parrent);
	parrent->right = create_ast_n(nodell->next->node, parrent);
	// free_lltab(sublsts);
}



// ===================================================================



t_redir	is_redir(t_node *node)
{
	if (!node)
		return (_NR);
	if (!ft_strncmp(node->val, ">", 1))
		return (_RED_R);
	if (!ft_strncmp(node->val, ">>", 1))
		return (_RED_DR);
	if (!ft_strncmp(node->val, "<", 1))
		return (_RED_L);
	return (_NR);
}

char 	**lltotab(t_node *lst, t_node *limiter)
{
	char	**out;
	int		count;
	t_node	*cpy;

	count = 0;
	cpy = lst;
	while (cpy && cpy != limiter)
	{
		count++;
		cpy = cpy->next;
	}
	out = ft_calloc(count + 1, sizeof(char *));
	if (!out)
		return (NULL);
	cpy = lst;
	count = 0;
	while (cpy && cpy != limiter)
	{
		out[count] = ft_strdup(cpy->val);
		count++;
		cpy = cpy->next;
	}
	out[count] = NULL;
	return (out);
}

t_node	*get_redir_node(t_node *head)
{
	t_node *cpy;

	cpy = head;
	while (cpy && !is_redir(cpy))
		cpy = cpy->next;
	return (cpy);
}

void	create_cmd(t_ast_n *self, t_node *lst)
{
	t_node	*sec_redir_node;

	self->state = _CMD;
	self->infile = NULL;
	self->outfile = NULL;
	if (is_redir(lst) != _NR)
	{
		self->cmd = ft_strdup(lst->next->next->val);
		self->args = lltotab(lst->next->next, NULL);
		self->infile = ft_strdup(lst->next->val); 
	}
	else
	{
		self->cmd = ft_strdup(lst->val);
		self->args = lltotab(lst, get_redir_node(lst->next));
	}
	sec_redir_node = get_redir_node(lst->next); 
	if (lst->next && sec_redir_node) 
	{
		self->outfile = ft_strdup(sec_redir_node->next->val); 
	}
	self->redir = is_redir(get_redir_node(lst)); 
}


//=====================================================================



void	create_pline(t_ast_n *self, t_node *lst, t_node *token)
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
		self->pline[i] = create_ast_n(cpy->node, self);
		cpy = cpy->next;
		i++;
	}
	cpy = NULL;
	// free_lltab(sublsts);
}





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

	ft_debug("================\n");
	ft_debug("NEW NODE CREATED\n");
	if (token && token->val)
		ft_debug("token val: %s\n", token->val);
	else
		ft_debug("token val : NULL\n");
	ft_debug("node state : %d\n", node->state);
	ft_debug("================\n\n");

	node->left = NULL;
	node->right = NULL;
	node->pline = NULL;
	node->parent = parent;

	if (node->state == _AND || node->state == _OR)
		create_and_or(node, lst, token);
	else if (node->state == _SUBSH)
		create_subsh(node, lst);
	else if (node->state == _PLINE)
		create_pline(node, lst, token);
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
