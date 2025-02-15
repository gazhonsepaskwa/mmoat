/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:08:49 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 11:59:55 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_null_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	**copy_env_var(char **envp, int count)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	new_env[count] = NULL;
	while (envp[i] && i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		free_null_ptr(envp[i]);
		i++;
	}
	free_null_ptr(envp);
	return (new_env);
}

int	count_var(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (-1);
	while (envp[i])
		i++;
	return (i);
}

char	*get_var_value(char	*key, char **envp)
{
	char	*tmp;
	int		i;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tmp, ft_strlen(tmp)) == 0)
		{
			free_null_ptr(tmp);
			return (ft_strchr(envp[i], '=') + 1);
		}
		i++;
	}
	free_null_ptr(tmp);
	return (NULL);
}

bool	is_valid_key(char *key, t_msh *msh)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (false);
	while (msh->env[i])
	{
		if (ft_strncmp(msh->env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free_null_ptr(tmp);
			return (true);
		}
		i++;
	}
	free_null_ptr(tmp);
	return (false);
}
