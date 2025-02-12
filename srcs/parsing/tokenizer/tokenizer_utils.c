/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:24:05 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/11 16:33:45 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_meta(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == ';' || c == '{' || c == '}' || c == '[' || c == ']')
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
		if (ft_str_count(it->val, 39) == 1 || ft_str_count(it->val, '"') == 1)
		{
			if (!in_quote)
				in_quote = it->val[0];
			else if (it->val[0] == in_quote)
				in_quote = 0;
		}
		if (!in_quote)
		{
			tmp = ft_strtrim(it->val, " \t\n");
			free(it->val);
			it->val = tmp;
		}
		it = it->next;
	}
	return (1);
}
