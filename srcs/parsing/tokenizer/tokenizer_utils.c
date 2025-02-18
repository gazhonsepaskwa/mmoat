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
#include <stdbool.h>

int	is_meta(char c)
{
	if (c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')'
		|| c == ';' || c == '{' || c == '}' || c == '[' || c == ']')
		return (1);
	return (0);
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
		tmp = ft_strtrim(it->val, " \t\n");
		free(it->val);
		it->val = tmp;
		it = it->next;
	}
	return (1);
}

static bool is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	else
	 return (false);
}

int	goto_nxt_space(char *str)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;

	in_squote = false;
	in_dquote = false;
	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] && (!is_space(str[i]) || (in_dquote || in_squote)))
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '\"' && !in_squote)
			in_dquote = !in_dquote;
		i++;
	}
	return (i);
}
