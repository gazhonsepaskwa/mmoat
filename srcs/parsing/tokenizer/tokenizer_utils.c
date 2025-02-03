/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:05 by nalebrun          #+#    #+#             */
/*   Updated: 2025/01/22 14:24:05 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_meta(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == '"' || c == 39)
		return (1);
	return (0);
}

int	is_sticked(char *val)
{
	int	i;
	int	meta;
	int	unmeta;

	i = 0;
	meta = 0;
	unmeta = 0;
	while (val[i])
	{
		if (is_meta(val[i]))
			meta = 1;
		if (!is_meta(val[i]))
			unmeta = 1;
		i++;
	}
	if (meta && unmeta)
		return (1);
	return (0);
}

int	ft_str_count(char *s, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] == c)
			count++;
	return (count);
}

int	trim_nodes(t_node *head)
{
	t_node	*it;
	char	*tmp;
	char	in_quote;

	it = head;
	in_quote = 0;
	while (it != NULL)
	{
		if (ft_str_count(it->val, 39) == 1
			|| ft_str_count(it->val, '"') == 1)
		{
			if (!in_quote)
				in_quote = it->val[0];
			else if (it->val[0] == in_quote)
				in_quote = 0;
		}
		if (!in_quote)
		{
			tmp = ft_strtrim(it->val, " \t\n");
			if (!tmp)
				return (0);
			free(it->val);
			it->val = tmp;
		}
		it = it->next;
	}
	return (1);
}

int	find_quote_node(t_node *head, char q)
{
	t_node	*it;

	it = head;
	while (it != NULL)
	{
		if (it->val[0] == q)
			return (1);
		it = it->next;
	}
	return (0);
}
