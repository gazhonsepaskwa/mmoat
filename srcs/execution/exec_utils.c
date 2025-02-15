/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:57:39 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/15 09:22:23 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execis_validchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	execget_var_len(char *str, t_ast_n *node, int *j)
{
	int		len;
	int		ret;
	char	*var;

	len = *j + 1;
	while (str[len] && execis_validchar(str[len]))
		len++;
	var = ft_substr(str, *j + 1, (size_t)len - (*j + 1));
	*j = len;
	ret = ft_strlen(get_var_value(var, node->msh->env));
	ft_free(&var);
	return (ret - (len - (*j + 1)));
}

int	get_dup_len(char *str, t_ast_n *node)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			len += execget_var_len(str, node, &i);
			i--;
		}
		i++;
	}
	return (len);
}

int	execvalid_next(char c)
{
	if (c != '\0' && execis_validchar(c))
		return (1);
	return (0);
}

char	*execextract_env(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 1;
	tmp = NULL;
	while (str[i] && execis_validchar(str[i]))
		i++;
	if (i > 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	ft_free(&tmp);
	return (var);
}
