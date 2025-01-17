/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:27:57  by nalebrun         #+#    #+#             */
/*   Updated: 2025/01/15 13:27:57  by nalebrun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static t_node	*tokenize_base(char *str)
{
	int		i;
	t_node	*head;
	char	**tab;

	tab = ft_split(str, " \t\n");
	if (!tab)
		return (NULL);
	head = create_node(tab[0], 0);
	if (!head)
		return (free(tab), NULL);
	i = 1;
	while (tab[i])
	{
		if (!add_node_back(head, tab[i], 0))
			return (free(tab), NULL);
		i++;
	}
	free_tab(tab);
	return (head);
}

static void	set_token(t_node *head)
{
	t_node *it;

	it = head;
	while (it != NULL)
	{
		it->token = get_token(it->val);
		it = it->next;
	}
}

static int	unstick_nodes(t_node *head)
{
	t_node *it;

	it = head;
	while (it != NULL)
	{
		if (is_sticked(it->val)) // undefined fct for the moment 
		{
			// if meta -> first part = jusqua plus meta
			// else -> first part = jusqua meta
			// secnd part = rest
			// it->val = first part
			// create a new node after [create_node_after()] with the second part of the string
		}
		it = it->next;
	}
	return (1);
}

t_node	*tokenize(char *str)
{
	t_node	*head;

	head = tokenize_base(str);
	if (!head)
		return (NULL);
	debug_linked_list(head, "base tokenized");
	if (!unstick_nodes(head))
		return (NULL);
	debug_linked_list(head, "nodes unsticked");
	// stick_quote_node(head);
	// debug_linked_list(head);
	set_token(head);
	debug_linked_list(head, "token set");
	return (head);
}
