/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:58:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/08 10:53:48 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_validchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	get_var_len(t_ast_n *node, int j , int *i)
{
	int len;
	int	ret;
	char *str;

	len = *i + 1;
	while (node->args[j][len] && is_validchar(node->args[j][len]))
		len++;
	str = ft_substr(node->args[j], *i + 1, (size_t)len - (*i + 1));
	*i = len;
	ret = ft_strlen(get_var_value(str, node->msh->env));
	ft_free(&str);
	return (ret - (len  - (*i + 1)));
}

static char	*extract_env(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 1;
	while (str[i] && is_validchar(str[i]))
		i++;
	if (i > 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	free(tmp);
	return (var);
}

static int	get_new_len(t_ast_n *node, int j)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(node->args[j]);
	while (node->args[j][i])
	{
		if (node->args[j][i] == '$')
		{
			len += get_var_len(node, j , &i);
			i--;
		}
		i++;
	}
	return (len);
}

int	valid_next(char c)
{
	if (c != '\0' && is_validchar(c))
		return (1);
	return (0);
}

void	expander_var(t_ast_n *node, int j)
{
	int	i;
	int k;
	int	len;
	char	*new;

	i = -1;
	len = get_new_len(node, j);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return ;
	k = 0;
	while (node->args[j][k] && ++i < len)
	{
		if (node->args[j][k] != '$')
			new[i] = node->args[j][k++];
		else if (node->args[j][k] == '$' && valid_next(node->args[j][k + 1]))
		{
			ft_strlcat(new, extract_env(&node->args[j][k], node->msh->env), -1);
			i = ft_strlen(new) - 1;
			while (node->args[j][++k] && is_validchar(node->args[j][k]))
				continue ;
		}
	}
	ft_free(&node->args[j]);
	node->args[j] = new;
}

int	in_squote(char *str, char *ch)
{
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (0);
	else if (ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
	{
		if ((ch > ft_strchr(str, '\'')) && ch < ft_strrchr(str, '\''))
			return (1);
		return (0);
	}
	else if (!ft_strchr(str, '\'') && ft_strchr(str, '\"'))
		return (0);
	else
	{
		if (ft_strchr(str, '\'') < ft_strchr(str, '\"'))
		{
			if ((ch > ft_strchr(str, '\'')) && ch < ft_strrchr(str, '\''))
				return (1);
			return (0);
		}
		return (0);
	}
}

int	expand_var(t_ast_n *node, int j)
{
	int	i;

	i = 0;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '$' && !in_squote(node->args[j], &node->args[j][i]))
			return (expander_var(node, j), 1);
		i++;
	}
	return (0);
}
