/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:22:16 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/03 15:44:56 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <unistd.h>

// ===================================================================

t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent, t_msh *msh);

// ====================================================================


void	create_and_or(t_ast_n *parrent, t_node *lst, t_node *token, t_msh *msh)
{
	t_nodell *nodell;

	nodell = cutll(lst, token, 1);
	parrent->left = create_ast_n(nodell->node, parrent, msh);
	parrent->right = create_ast_n(nodell->next->node, parrent, msh);
	// free_lltab(sublsts);
}



// ===================================================================



t_redir	get_redir(t_node *node)
{
	if (!node)
		return (_NR);
	else if (!ft_strncmp(node->val, ">>", 2))
		return (_RED_DR);
	else if (!ft_strncmp(node->val, ">", 1))
		return (_RED_R);
	else if (!ft_strncmp(node->val, "<<", 2))
		return (_RED_DL);
	else if (!ft_strncmp(node->val, "<", 1))
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

void add_redir(t_redir redir, t_redir **redir_list)
{
    int     i;
    int     j;
    t_redir *tmp;

    i = 0;
    while ((*redir_list)[i] != _NR)
        i++;
    tmp = ft_calloc(i + 2, sizeof(t_redir));
    j = -1;
    while ((*redir_list)[++j] != _NR)
        tmp[j] = (*redir_list)[j];
    tmp[j++] = redir;
    tmp[j] = _NR;
    free(*redir_list);
    *redir_list = tmp;
}

void	create_redir(t_node *cpy, t_ast_n *self)
{
	t_redir redir;

	while (cpy && cpy->next && get_redir(cpy) == _NR)
	{
		redir = get_redir(cpy);
		add_redir(redir, &self->redir);
		add_to_tab(&self->files, cpy->next->val);
		cpy = cpy->next;
		while (cpy && cpy->next && get_redir(cpy) == _NR)
			cpy = cpy->next;
	}
}

t_node	*get_cmd(t_node *lst)
{
	while (lst)
	{
		if (get_redir(lst) != _NR && lst->next && lst->next->next && get_redir(lst->next->next) == _NR)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	create_cmd(t_ast_n *self, t_node *lst)
{
	t_node	*cpy;
	t_node	*cmd_node;

	self->state = _CMD;
	self->files = NULL;
	self->redir = ft_calloc(1, sizeof(t_redir));
	self->redir[0] = _NR; 
	cmd_node = get_cmd(lst);
	self->cmd = cmd_node->val;
	self->args = ft_split("NOT SET", " ");
	cpy = lst;
	create_redir(cpy, self);
}


//=====================================================================



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
		self->pline[i] = create_ast_n(cpy->node, self, msh);
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



//==================================================================



t_ast_n	*create_ast_n(t_node *lst, t_ast_n *parent, t_msh *msh)
{
	t_ast_n *node;
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
	t_ast_n *head;

	head = create_ast_n(lst, NULL, msh);
	return (head);
}
