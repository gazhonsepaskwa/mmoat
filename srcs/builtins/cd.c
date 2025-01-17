#include "../../includes/builtins.h"

int	count_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**update_oldpwd(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 1);
	if (!new_envp)
		return (perror("malloc"), NULL);
	new_envp[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "OLDPWD=", 7) == NULL)
			new_envp[i] = ft_strdup(envp[i]);
		else
			new_envp[i] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	}
	return (new_envp);
}

char	**update_pwd(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 1);
	if (!new_envp)
		return (perror("malloc"), NULL);
	new_envp[i] = NULL;
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "PWD=", 4) == NULL)
			new_envp[i] = ft_strdup(envp[i]);
		else
			new_envp[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
	}
	return (new_envp);
}

int	check_path(char *str)
{
	if (access(str, F_OK | X_OK) == -1)
	{
		ft_put_s_fd(str, 2);
		ft_put_s_fd(": ", 2);
		perror("cd");
		return (0);
	}
	return (1);
}

// void	expand_var(char *str, char **envp)
// {
// 	char	*new_arg;
// 	char	*tmp;
// 	int		i;
// 	int 	j;
//
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			j = 0;
// 			while (str[j] && str[j] != ' ')
// 				j++;
// 			if (j >= 1)
// 		}
// 	}
// }

char	**builtin_cd(char **arg, char **envp)
{
	// char *path;

	if (count_args(arg) >= 3)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (envp);
	}
	// path = expand_var(arg[1], envp);
	if (!check_path(arg[1]))
		return (envp);
	envp = update_oldpwd(envp);
	if (chdir(arg[1]) == -1)
	{
		perror("cd");
		return (envp);
	}
	envp = update_pwd(envp);
	return (envp);
}
