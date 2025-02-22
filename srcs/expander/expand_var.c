/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:58:25 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/17 09:12:39 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <stdbool.h>

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
	tmp = NULL;
	while (str[i] && is_exvalidchar(str[i]))
		i++;
	if (i > 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	free(tmp);
	return (var);
}

int	expand_exit(t_ast_n *node, int j, int i)
{
	int		k;
	char	*new;
	char	*num;
	char	*ret;
	int		len;

	k = -1;
	if (node->args[j][i + 1] && node->args[j][i + 1] == '?')
	{
		num = ft_itoa(node->msh->ex_code);
		len = ft_strlen(num);
		new = ft_calloc(ft_strlen(node->args[j]) + len + 1, 1);
		if (!new)
			return (0);
		ret = new;
		while (++k < i)
			*new++ = node->args[j][k];
		ft_strlcat(new, num, -1);
		ft_strlcat(new, &node->args[j][i + 2], -1);
		ft_free(&num);
		ft_free(&node->args[j]);
		node->args[j] = ret;
		return (1);
	}
	return (0);
}

void	expander_var(t_ast_n *nd, int j, int i)
{
	char	*new;
	char	*ret;
	char	*var;
	int		k;
	int		l;

	k = i;
	if (expand_exit(nd, j, i))
		return ;
	new = ft_calloc(ft_strlen(nd->args[j]) + get_var_len(nd, j, &k), 1);
	if (!new)
		return ;
	ret = new;
	l = -1;
	while (++l < i)
		*new++ = nd->args[j][l];
	var = extract_env(&nd->args[j][i], nd->msh->env);
	ft_strlcat(new, var, -1);
	ft_strlcat(new, &nd->args[j][k], -1);
	ft_free(&nd->args[j]);
	nd->args[j] = ret;
}

int	expand_var(t_ast_n *node, int j)
{
	int		i;
	bool	in_squote;
	bool	in_dquote;
	int		ret;

	in_squote = false;
	in_dquote = false;
	i = 0;
	ret = 0;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (node->args[j][i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (node->args[j][i] == '$' && !in_squote)
		{
			ret = 1;
			expander_var(node, j, i);
		}
		i++;
	}
	return (ret);
}
