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

static t_node	*create_head(int *depth, char *str, char *last_token)
{
	t_node	*head;
	char	*token;

	ajust_depth(depth, str[0]);
	token = copy_token_string(&str[0], *last_token);
	if (!(*token))
		return (NULL);
	head = create_node(token, get_priority(token), *depth);
	if (!head)
		return (NULL);
	*last_token = str[0];
	free(token);
	return (head);
}

t_node	*tokenize(char *str)
{
	int		i;
	int		depth;
	char	*token;
	t_node	*head;
	char	last_token;

	depth = 0;
	last_token = ' ';
	head = create_head(&depth, str, &last_token);
	i = goto_next_token(&str[0]);
	while (str[i])
	{
		ajust_depth(&depth, str[i]);
		token = copy_token_string(&str[i], last_token);
		if (!token)
			return (NULL);
		if (token[0] != 0)
			add_node_back(head, depth, token);
		while (str[i] == ' ')
			i++;
		last_token = str[i];
		i += goto_next_token(&str[i]);
		free(token);
	}
	return (head);
}
