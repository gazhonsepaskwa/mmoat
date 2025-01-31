/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:56:34 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/31 10:32:03 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	add_nodell(t_nodell **nodell, t_node *node)
{
	while (*nodell)
		*nodell = (*nodell)->next;
	(*nodell) = malloc(sizeof(t_nodell));
	(*nodell)->node = node;
	(*nodell)->next = NULL;
}

t_node *get_node(t_node *lst, char *expected)
{
	t_node	*node;

	node = NULL;
	while (lst && ft_strncmp(lst->val, expected, ft_strlen(expected)))
	{
		add_node_back(&node, lst->val, lst->token, lst->pressision);
		lst = lst->next;
	}
	return (node);
}

t_nodell	*cutll(t_node *lst, char *expected, size_t limiter)
{
	t_nodell	*out;
	t_node		*node;
	size_t		i;
	
	i = 0;
	out = NULL;
	while (i <= limiter)
	{
		node = get_node(lst, expected);
		if (!node)
			break;
		add_nodell(&out, node);
		i++;
	}
	return (out);
}
