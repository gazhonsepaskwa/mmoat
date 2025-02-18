/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:56:34 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 17:56:37 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	add_nodell(t_nodell **nodell, t_node *node)
{
	t_nodell	*tmp;

	if (!nodell || !(*nodell))
	{
		*nodell = malloc(sizeof(t_nodell));
		(*nodell)->node = node;
		(*nodell)->next = NULL;
		return ;
	}
	tmp = *nodell;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_nodell));
	tmp->next->node = node;
	tmp->next->next = NULL;
}

static void	update_subsh_l(int *shlvl, t_node *lst)
{
	if (!lst)
		return ;
	if (!ft_strncmp(")", lst->val, 1))
		*shlvl -= 1;
	if (!ft_strncmp("(", lst->val, 1))
		*shlvl += 1;
}

static t_node	*get_node(t_node **lst, t_node *expected,
						int limiter, int *shlvl)
{
	t_node	*node;

	node = NULL;
	while (limiter != -1 && (*lst) && (*lst) != expected)
	{
		add_node_back(&node, (*lst)->val, (*lst)->token, (*lst)->pressision);
		(*lst) = (*lst)->next;
	}
	while (limiter == -1 && (*lst)
		&& (*shlvl >= 2
			|| ft_strncmp((*lst)->val, expected->val, ft_strlen((*lst)->val))))
	{
		update_subsh_l(shlvl, *lst);
		add_node_back(&node, (*lst)->val, (*lst)->token, (*lst)->pressision);
		(*lst) = (*lst)->next;
	}
	return (node);
}

t_nodell	*cutll(t_node *lst, t_node *expected, size_t limiter)
{
	t_nodell	*out;
	t_node		*node;
	size_t		i;
	t_nodell	*tmp;
	int			shlvl;

	i = 0;
	out = NULL;
	shlvl = 0;
	while (i <= limiter)
	{
		update_subsh_l(&shlvl, lst);
		node = get_node(&lst, expected, limiter, &shlvl);
		if (!node)
			break ;
		add_nodell(&out, node);
		tmp = out;
		while (tmp)
			tmp = tmp->next;
		if (!lst)
			break ;
		lst = lst->next;
		i++;
	}
	return (out);
}

void	free_lltab(t_nodell *nodell)
{
	t_nodell	*tmp;

	while (nodell)
	{
		free_linked_list(nodell->node);
		tmp = nodell->next;
		free(nodell);
		nodell = tmp;
	}
}
