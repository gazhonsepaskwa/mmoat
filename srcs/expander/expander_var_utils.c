/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:17:28 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 11:01:55 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/expander.h"

int	expand_exit(t_ast_n *node, int j, int k)
{
	if (node->args[j][k] == '$' && (node->args[j][k + 1]
		&& node->args[j][k + 1] == '?')
		&& !in_squote(node->args[j], &node->args[j][k]))
	{
		return (1);
	}
	return (0);
}

int	valid_expand(t_ast_n *node, int j, int k)
{
	if (node->args[j][k] == '$' && exvalid_next(node->args[j][k + 1])
		&& !in_squote(node->args[j], &node->args[j][k]))
	{
		return (1);
	}
	return (0);
}

char	*create_new(t_ast_n *node, int j, int *len)
{
	char	*new;

	*len = get_new_len(node, j);
	new = ft_calloc(*len + 1, sizeof(char));
	return (new);
}

void	handle_copy(t_ast_n *node, int j, char **new)
{
	ft_free(&node->args[j]);
	node->args[j] = *new;
}

void	cat_exit(t_ast_n *node, char **new, int *i, int *k)
{
	char	*itoa;

	itoa = ft_itoa(node->msh->ex_code);
	ft_strlcat(*new, itoa, -1);
	*i = ft_strlen(*new) - 1;
	*k += 2;
	free(itoa);
}
