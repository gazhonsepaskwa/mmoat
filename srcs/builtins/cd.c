#include "../../includes/builtins.h"

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

char	**builtin_cd(char **arg, char **envp)
{
	/*
	 * OLDPWD = getcwd()
	 */
	envp = update_oldpwd(envp);
	if (chdir(arg[1]) == -1)
	{
		perror("cd");
		return (envp);
	}
	envp = update_pwd(envp);
	/*
	 * PWD = getcwd()
	 */
	return (envp);
}
