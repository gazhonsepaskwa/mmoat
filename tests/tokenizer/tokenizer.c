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

int	important_token(char c)
{
	if (c == '(' || c == ')'
		|| c == '|' || c == '&')
		return (1);
	return (0);
}

char *copy_token_string(char *start)
{
	char	*out;
	int		i;
	int		j;

	i = 0;
	while (start[i] && start[i] == ' ')
		i++;
	if (start[i] == '&')
		i = 2;
	else if (start[i] == '|' && start[i + 1] && start[i + 1] == '|')
		i = 2;
	else if (start[i] == '|' && start[i + 1] && start[i + 1] != '|')
		i = 1;
	else if (start[i] == '(')
		i = 1;
	else if (start[i] == ')')
		i = 1;
	else
	{
		while (start [i]
			&& start[i] != '&'
			&& start[i] != '|'
			&& start[i] != '('
			&& start[i] != ')')
		i++;
	}
	out = malloc(i + 1);
	if (!out)
		return (NULL);
	j = -1;
	while (++j < i)
		out[j] = start[j];
	out[j] = 0;
	return (out);
}

int	goto_next_token(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '(' || str[0] == ')')
	{
		if (str[1] && str[1] == ' ')
			return (2);
		else
			return (1);
	}
	else if (str[0] == '&' && str[1] && str[1] == '&')
		return (2);
	else if (str[0] == '|' && str[1] && str[1] == '|')
		return (2);
	else if (str[0] == '|' && str[1] && str[1] != '|' && str[1] && str[1] == ' ')
		return (2);
	else if (str[0] == '|' && str[1] && str[1] != '|' && str[1] != ' ')
		return (1);
	else
	{
		while (str[i] && str[i] != '&' && str[i] != '|'
				&& str[i] != '(' && str[i] != ')')
			i++;
		if (str[i] == ' ')
			i++;
	}
	return (i);
}

t_node	*tokenize(char *str)
{
	int		i;
	int		depth;
	char	*token;
	char	*trimed_token;
	t_node	*head;

	i = 0;
	depth = 0;
	ajust_depth(&depth, str[i]);
	token = copy_token_string(&str[i]);
	if (!token)
		return (NULL);
	trimed_token = ft_strtrim(token, " ");
	head = create_node(trimed_token, get_priority(trimed_token), depth);
	free(token);
	free(trimed_token);
	i += goto_next_token(&str[i]);
	while(str[i])
	{
		ajust_depth(&depth, str[i]);
		token = copy_token_string(&str[i]);
		if (!token)
			return (NULL);
		trimed_token = ft_strtrim(token, " ");
		if (trimed_token[0] != 0)
			add_node_back(head, depth, trimed_token);
		free(token);
		free(trimed_token);
		i += goto_next_token(&str[i]);
	}
	return (head);
}
