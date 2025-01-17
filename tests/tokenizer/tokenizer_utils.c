/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:38:49  by nalebrun         #+#    #+#             */
/*   Updated: 2025/01/15 13:38:49  by nalebrun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_node	*create_node(char *token, int priority, int depth)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->token = ft_strdup(token);
	node->priority = priority;
	node->depth = depth;
	node->next = NULL;
	return (node);
}

int	get_priority(char *token)
{
	int	priority;

	if (token[0] == '&' && token[1] && token[1] == '&')
		priority = 2;
	else if (token[0] == '|' && token[1] && token[1] == '|')
		priority = 2;
	else if (token[0] == '|')
		priority = 1;
	else
		priority = 0;
	return (priority);
}

void	add_node_back(t_node *head, int depth, char *token)
{
	while (head->next != NULL)
		head = head->next;
	head->next = create_node(token, get_priority(token), depth);
}

void	ajust_depth(int *depth, char c)
{
	if (c == '(')
		(*depth) += 1;
	if (c == ')')
		(*depth) -= 1;
}
