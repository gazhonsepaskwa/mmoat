/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:08:49 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/03 13:10:32 by lderidde         ###   ########.fr       */
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
			&& (ft_strchr(msh->env[i], '=') == NULL && 
			(ft_strlen(msh->env[i]) == ft_strlen(key))))
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

	i = get_var_index(key, msh);
	if (value)
		tmp = ft_strjoin(key, "=");
	if (!tmp)
		return ;
	if (i != -1 && msh->env[i])
	{
		free_null_ptr(msh->env[i]);
		msh->env[i] = ft_strjoin(tmp, value);
	}
	else
	{
		i = count_var(msh->env);
		msh->env = copy_env_var(msh->env, i + 1);
		if (!msh->env)
			return ;
		msh->env[i] = ft_strjoin(tmp, value);
	}
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
