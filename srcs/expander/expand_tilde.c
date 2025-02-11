/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:56:32 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/08 13:15:52 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_new_len(t_ast_n *node, int j)
{
	int	i;
	int	len;

	i = -1;
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

size_t	ft_astrlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst || !src)
		return (0);
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	i = -1;
	while (src[++i] && (dst_len + i) < (dstsize - 1))
		dst[dst_len + i] = src[i];
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

void	expander_tilde(t_ast_n *node, int j)
{
	int		i;
	int		len;
	int		save;
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
			ft_astrlcat(new, get_var_value("HOME", node->msh->env), -1);
			i = ft_strlen(new) - 1;
			len++;
		}
	}
	ft_free(&node->args[j]);
	node->args[j] = new;
}

int	expand_tilde(t_ast_n *node, int j)
{
	int	i;

	i = 0;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '~')
			return (expander_tilde(node, j), 1);
		i++;
	}
	return (0);
}
