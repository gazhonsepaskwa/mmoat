/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:58:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 11:02:35 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_var_len(t_ast_n *node, int j, int *i)
{
	int		len;
	int		ret;
	char	*str;

	len = *i + 1;
	while (node->args[j][len] && is_exvalidchar(node->args[j][len]))
		len++;
	str = ft_substr(node->args[j], *i + 1, (size_t)len - (*i + 1));
	*i = len;
	ret = ft_strlen(get_var_value(str, node->msh->env));
	ft_free(&str);
	return (ret - (len - (*i + 1)));
}

static char	*extract_env(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 1;
	while (str[i] && is_exvalidchar(str[i]))
		i++;
	if (i > 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	free(tmp);
	return (var);
}

int	get_new_len(t_ast_n *node, int j)
{
	int		i;
	int		len;
	char	*itoa;

	i = 0;
	len = ft_strlen(node->args[j]);
	while (node->args[j][i])
	{
		if (node->args[j][i] == '$' && (node->args[j][i + 1]
			&& node->args[j][i + 1] == '?')
			&& !in_squote(node->args[j], &node->args[j][i]))
		{
			itoa = ft_itoa(node->msh->ex_code);
			len += ft_strlen(itoa) - 2;
			free(itoa);
		}
		else if (node->args[j][i] == '$' &&
			!in_squote(node->args[j], &node->args[j][i]))
		{
			len += get_var_len(node, j, &i);
			i--;
		}
		i++;
	}
	return (len);
}

void	expander_var(t_ast_n *nd, int j)
{
	int		i;
	int		k;
	int		len;
	char	*new;

	i = -1;
	new = create_new(nd, j, &len);
	if (!new)
		return ;
	k = 0;
	while (nd->args[j][k] && ++i < len)
	{
		if (nd->args[j][k] != '$' || in_squote(nd->args[j], &nd->args[j][k]))
			new[i] = nd->args[j][k++];
		else if (expand_exit(nd, j, k))
			cat_exit(nd, &new, &i, &k);
		else if (valid_expand(nd, j, k))
		{
			ft_strlcat(new, extract_env(&nd->args[j][k], nd->msh->env), -1);
			i = ft_strlen(new) - 1;
			while (nd->args[j][++k] && is_exvalidchar(nd->args[j][k]))
				continue ;
		}
	}
	handle_copy(nd, j, &new);
}

int	expand_var(t_ast_n *node, int j)
{
	int	i;

	i = 0;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '$' &&
			!in_squote(node->args[j], &node->args[j][i]))
			return (expander_var(node, j), 1);
		i++;
	}
	return (0);
}
