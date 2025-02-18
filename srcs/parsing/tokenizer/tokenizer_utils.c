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

static int	skip_quote(char *str)
{
	int i;

	if (!str[1])
		return 0;
	i = 1;
	while(str[i] && str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}

int	goto_nxt_space(char *str)
{
	int		i;

	i = 0;
	while (is_space(str[i]))
		i++;
	while (str[i] && !is_space(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			i += skip_quote(&(str[i]));
		i++;
	}
	return (i);
}
