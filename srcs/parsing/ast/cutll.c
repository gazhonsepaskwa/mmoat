/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:56:34 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/31 14:05:12 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static t_node *get_node(t_node **lst, t_node *expected, int limiter)
{
	t_node	*node;

	node = NULL;
	while (limiter != -1 && (*lst) && (*lst) != expected)
	{
		add_node_back(&node, (*lst)->val, (*lst)->token, (*lst)->pressision);
		(*lst) = (*lst)->next;
	}
	while (limiter == -1 && (*lst) && ft_strncmp((*lst)->val, expected->val, ft_strlen((*lst)->val)))
	{
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
	
	i = 0;
	out = NULL;
	while (i <= limiter)
	{
		node = get_node(&lst, expected, limiter);
		if (!node)
			break;
		add_nodell(&out, node);
		t_nodell *tmp = out;
		while (tmp)
			tmp = tmp->next;
		if(lst && lst->next)
			lst = lst->next;
		i++;
	}
	return (out);
}
