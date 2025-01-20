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

bool	is_valid_key(char *key, t_data *data)
{
	char	*tmp;
	int		i;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (false);
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], tmp, ft_strlen(tmp)) == 0)
		{
			free_null_ptr(tmp);
			return (true);
		}
		i++;
	}
	free_null_ptr(tmp);
	return (false);
}

int	get_var_index(char *key, t_data *data)
{
	int		i;
	char	*new_key;

	new_key = ft_strjoin(key, "=");
	if (!new_key)
		return (-1);
	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], new_key, ft_strlen(new_key)) == 0)
		{
			free_null_ptr(new_key);
			return (i);
		}
		i++;
	}
	free_null_ptr(new_key);
	return (-1);
}


int	remove_env_var(char *key, t_data *data)
{
	int	i;
	int	j;

	i = get_var_index(key, data);
	if (i == -1)
		return (0);
	j = i;
	free_null_ptr(data->env[i]);
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_null_ptr(data->env[i + 1]);
		j++;
		i++;
	}
	data->env = copy_env_var(data->env, j);
	if (data->env)
		return (1);
	return (0);
}

void	set_var_env(char *key, char *value, t_data *data)
{
	int		i;
	char	*tmp;

	i = get_var_index(key, data);
	if (!value)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return ;
	if (i != -1 && data->env[i])
	{
		free_null_ptr(data->env[i]);
		data->env[i] = ft_strjoin(key, tmp);
	}
	else
	{
		i = count_var(data->env);
		data->env = copy_env_var(data->env, i + 1);
		if (!data->env)
			return ;
		data->env[i] = ft_strjoin(key, tmp);
	}
	free_null_ptr(tmp);
	return ;
}
