/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:09:37 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/10 13:29:09 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec/expander.h"
#include <dirent.h>
#include <stdbool.h>

static char	*_strfjoin(char *s1, char *s2)
{
	char			*out;
	unsigned int	i;
	unsigned int	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		out[i++] = s1[j++];
	j = 0;
	while (s2[j])
		out[i++] = s2[j++];
	free(s1);
	return (out);
}

bool	ft_fnmatch(const char *str, const char *pat)
{
	if (*pat == '\0' && *str == '\0')
		return (true);
	if (*pat == '*' && *(pat + 1) != '\0' && *str == '\0')
		return (false);
	if (*pat == *str)
		return (ft_fnmatch(str + 1, pat + 1));
	if (*pat == '*')
		return (ft_fnmatch(str, pat + 1) || ft_fnmatch(str + 1, pat));
	return (false);
}
void	handle_new(t_ast_n *node, int j, char *new)
{
	if (new)
	{
		ft_free(&node->args[j]);
		node->args[j] = new;
	}
}

void	expander_star(t_ast_n *node, int j, char *pat)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*new;

	new = NULL;
	dir = opendir(".");
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, ".", 1) == 0)
			entry = readdir(dir);
		else if (ft_fnmatch(entry->d_name, pat) == true)
		{
			if (new != NULL)
				new = _strfjoin(new, " ");
			new = _strfjoin(new, entry->d_name);	
			entry = readdir(dir);
		}
		else
			entry = readdir(dir);
	}	
	handle_new(node, j, new);
	closedir(dir);
}

static int	in_quote(char *str, char *ch)
{
	if (in_squote(str, ch) || in_dquote(str, ch))
		return (1);
	return (0);
}

int	expand_star(t_ast_n *node, int j)
{
	int	i;

	i = 0;
	while (node->args[j][i])
	{
		if (node->args[j][i] == '*' && !in_quote(node->args[j], &node->args[j][i]))
			return (expander_star(node, j, node->args[j]), 1);
		i++;
	}
	return (0);
}
