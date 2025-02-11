/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:36:27 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 15:36:27 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_var_index(char *key, t_msh *msh)
{
	int		i;
	char	*new_key;

	new_key = ft_strjoin(key, "=");
	if (!new_key)
		return (-1);
	i = 0;
	while (msh->env[i])
	{
		if (ft_strncmp(msh->env[i], new_key, ft_strlen(new_key)) == 0)
		{
			free_null_ptr(new_key);
			return (i);
		}
		else if (ft_strncmp(msh->env[i], key, ft_strlen(key)) == 0
			&& (ft_strchr(msh->env[i], '=') == NULL
				&& (ft_strlen(msh->env[i]) == ft_strlen(key))))
		{
			free_null_ptr(new_key);
			return (i);
		}
		i++;
	}
	free_null_ptr(new_key);
	return (-1);
}

int	remove_env_var(char *key, t_msh *msh)
{
	int	i;
	int	j;

	i = get_var_index(key, msh);
	if (i == -1)
		return (0);
	j = i;
	free_null_ptr(msh->env[i]);
	while (msh->env[i + 1])
	{
		msh->env[i] = ft_strdup(msh->env[i + 1]);
		free_null_ptr(msh->env[i + 1]);
		j++;
		i++;
	}
	msh->env = copy_env_var(msh->env, j);
	if (msh->env)
		return (1);
	return (0);
}

void	set_var_env(char *key, char *value, t_msh *msh)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = get_var_index(key, msh);
	if (value)
		tmp = ft_strjoin("=", value);
	if (value && !tmp)
		return ;
	if (i != -1 && msh->env[i])
	{
		free_null_ptr(msh->env[i]);
		msh->env[i] = ft_strjoin(key, tmp);
	}
	else
	{
		i = count_var(msh->env);
		msh->env = copy_env_var(msh->env, i + 1);
		if (!msh->env)
			return ;
		msh->env[i] = ft_strjoin(key, tmp);
	}
	if (tmp && tmp[0])
		free_null_ptr(tmp);
	return ;
}

char	**init_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	env = malloc(sizeof(char *) * (count_var(envp) + 1));
	if (!env)
		return (NULL);
	env[count_var(envp)] = NULL;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}
