/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:32 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/17 09:30:24 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

void	expander_tilde(t_ast_n *node, int j, int i, char *str)
{
	char	*new;
	char	*ret;
	char	*var;
	int		k;
	int		l;

	k = i;
	var = get_var_value("HOME", node->msh->env);
	new = ft_calloc(ft_strlen(str) + ft_strlen(var), 1);
	if (!new)
		return ;
	ret = new;
	l = -1;
	while (++l < i)
		*new++ = node->args[j][l];
	ft_strlcat(new, var, -1);
	ft_strlcat(new, &node->args[j][++i], -1);
	ft_free(&node->args[j]);
	node->args[j] = ret;
}

int	expand_tilde(t_ast_n *node, int j)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;
	int		ret;

	i = 0;
	ret = 0;
	in_squote = false;
	in_dquote = false;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (node->args[j][i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (node->args[j][i] == '~' && !in_squote)
		{
			ret = 1;
			expander_tilde(node, j, i, node->args[j]);
		}
		i++;
	}
	return (ret);
}
