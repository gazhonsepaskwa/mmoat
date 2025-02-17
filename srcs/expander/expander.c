/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:23:02 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:30:32 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

// void	remove_quote(t_ast_n *node, int j, char c)
// {
// 	char	*new;
// 	int		i;
// 	int		k;
// 	int		len;
//
// 	i = 0;
// 	k = 0;
// 	len = ft_strlen(node->args[j]);
// 	new = ft_calloc(len - 1, sizeof(char));
// 	while (i < len - 2)
// 	{
// 		if ((&(node->args[j][k]) == ft_strchr(node->args[j], c)) ||
// 			(&(node->args[j][k]) == ft_strrchr(node->args[j], c)))
// 		{
// 			k++;
// 		}
// 		else
// 			new[i++] = node->args[j][k++];
// 	}
// 	ft_free(&node->args[j]);
// 	node->args[j] = new;
// }
//
void	remove_quote(t_ast_n *node, int j, char *str)
{
	bool	in_squote;
	bool	in_dquote;
	char	*new;
	char	*ret;

	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new)
		return ;
	ret = new;
	in_squote = false;
	in_dquote = false;
	while (*str)
	{
		if (*str == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (*str == '\'' && !in_dquote)
			in_squote = !in_squote;
		else
			*new++ = *str;
		str++;
	}
	ft_free(&node->args[j]);
	node->args[j] = ret;
}

int	ifremove_quote(t_ast_n *node, int j)
{
	char	c;
	int		ret;

	ret = 0;
	if (!ft_strchr(node->args[j], '\'') && !ft_strchr(node->args[j], '\"'))
		c = 0;
	else if (!ft_strchr(node->args[j], '\"'))
		c = '\'';
	else if (!ft_strchr(node->args[j], '\''))
		c = '\"';
	else if (ft_strchr(node->args[j], '\'') < ft_strchr(node->args[j], '\"'))
		c = '\'';
	else
		c = '\"';
	if (c && (ft_strchr(node->args[j], c) != ft_strrchr(node->args[j], c)))
		remove_quote(node, j, node->args[j]);
	if (c)
		ret = 1;
	return (ret);
}

char	**arrange_tabs(t_ast_n *node, char **tab, int j)
{
	int		save;
	int		i;
	int		k;
	int		len;
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

	tab = ft_split(node->args[j], " ");
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
	while (node->args && node->args[++i])
	{
		check = 0;
		if (expand_tilde(node, i))
			check = 1;
		if (expand_var(node, i))
			check = 1;
		if (!ifremove_quote(node, i) && check)
		{
			split_tab(node, i);
			if (!node->args[i])
				i--;
			check = 0;
		}
		check = expand_star(node, i);
		if (check)
			split_tab(node, i);
		ft_free(&node->cmd);
		node->cmd = ft_strdup(node->args[0]);
	}
	return (node);
}
