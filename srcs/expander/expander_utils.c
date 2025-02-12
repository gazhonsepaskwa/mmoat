/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:28:57 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:30:27 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	in_dquote(char *str, char *ch)
{
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (0);
	else if (ft_strchr(str, '\"') && !ft_strchr(str, '\''))
	{
		if ((ch > ft_strchr(str, '\"')) && ch < ft_strrchr(str, '\"'))
			return (1);
		return (0);
	}
	else if (!ft_strchr(str, '\"') && ft_strchr(str, '\''))
		return (0);
	else
	{
		if (ft_strchr(str, '\"') < ft_strchr(str, '\''))
		{
			if ((ch > ft_strchr(str, '\"')) && ch < ft_strrchr(str, '\"'))
				return (1);
			return (0);
		}
		return (0);
	}
}

int	is_exvalidchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	exvalid_next(char c)
{
	if (c != '\0' && is_exvalidchar(c))
		return (1);
	return (0);
}
