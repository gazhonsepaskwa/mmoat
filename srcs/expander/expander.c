/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:23:02 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 12:31:57 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_new_len(t_ast_n *node, int j)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(node->args[j]);
	while (node->args[j][++i])
	{
		if (node->args[j][i] == '~')
		{
			len += ft_strlen(get_var_value("HOME", node->msh->env)) - 1;
		}
	}
	return (len);
}

void	expand_tilde(t_ast_n *node, int j)
{
	int i;
	int	len;
	int	save;
	char	*new;

	i = -1;
	len = get_new_len(node, j);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return ;
	save = len;
	len = 0;
	while (++i < save)
	{
		if (node->args[j][len] != '~')
			new[i] = node->args[j][len++];
		else
		{
			ft_strlcat(new, get_var_value("HOME", node->msh->env), -1);
			i = ft_strlen(new) - 1;
			len++;
		}
	}
	ft_free(&node->args[j]);
	node->args[j] = new;
}

t_ast_n	*expand_node(t_ast_n *node)
{
	int	i;

	i = -1;
	while (node->args[++i])
	{
		expand_tilde(node, i);
	}
	return (node);
}
