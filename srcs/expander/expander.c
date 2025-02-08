/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:23:02 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/08 14:10:50 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/expander.h"

int remove_quote(t_ast_n *node, int j)
{
	char	*new;
	int	ret;

	ret = 0;
	if (node->args[j][0])
	{
		if (node->args[j][0] == '\'' || node->args[j][0] == '\"')
			ret = 1;
	}
	new = ft_strtrim(node->args[j], "'\"");
	ft_free(&node->args[j]);
	node->args[j] = new;
	return (ret);
}

char	**arrange_tabs(t_ast_n *node, char **tab, int j)
{
	int	save;
	int	i;
	int	k;
	int	len;
	char	**new_arg;

	i = 0;
	k = 0;
	len = 0;
	save = count_var(node->args) + count_var(tab);
	new_arg = ft_calloc(sizeof(char *), save);
	while (i < save - 1)
	{
		if (i == j)
		{
			while (tab[k])
				new_arg[i++] = ft_strdup(tab[k++]);
			len++;
		}
		else
			new_arg[i++] = ft_strdup(node->args[len++]);
	}
	return (new_arg);
}

void	split_tab(t_ast_n *node, int j)
{
	char	**tab;
	char	**new_arg;


	tab =ft_split(node->args[j], " ");
	new_arg = arrange_tabs(node, tab, j);
	free_tab(tab);
	free_tab(node->args);
	node->args = new_arg;
}

t_ast_n	*expand_node(t_ast_n *node)
{
	int	i;
	int	check;

	i = -1;
	while (node->args[++i])
	{
		check = 0;
		if (expand_tilde(node, i))
			check = 1;
		if (expand_var(node, i))
			check = 1;
		if (check && !remove_quote(node, i))
			split_tab(node, i);
		(void)check;
	}
	return (node);
}
