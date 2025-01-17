#include "../includes/minishell.h" 

char	*powerline(void)
{
	char	*pwd;
	char	*tilt;

	pwd = getcwd(NULL, 0);
	if (ft_strncmp(pwd, "/home/", 6) == 0)
	{
		pwd = pwd + 6;
		while ((*pwd) != '/')
			pwd = pwd + 1;
		tilt = " ~";
	}
	else
		tilt = " ";
	printf("%s----------------------------------------------\
----------------------------------%s", POW5, RESET);
	printf("\n%s   MMOAT %s%s%s%s%s %s%s%s ",
		POW1, POW2, POW3, POW4, tilt, pwd, RESET, POW5, RESET);
	return (readline(""));
}

char	**ft_setnewenv(void)
{
	char **envp;

	envp = malloc(sizeof(char *) * 2);
	if (!envp)
		return (NULL);
	envp[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	envp[1] = ft_strdup("SHLVL=1");
	if (!envp[0] || !envp[1])
		return (ft_free(&envp[0]), ft_free(&envp[1]), NULL);
	return (envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	if (!envp[0])
		envp = ft_setnewenv();
	while (1)
	{
		input = powerline();
		if (ft_strncmp(input, "exit", 4) == 0)
			builtin_exit(input, true);
		if (ft_strncmp(input, "pwd", 3) == 0)
			builtin_pwd(input);
		if (ft_strncmp(input, "echo", 4) == 0)
			builtin_echo(input, envp);
		if (ft_strncmp(input, "env", 3) == 0)
			builtin_env(input, envp);
		if (ft_strncmp(input, "unset", 5) == 0)
			builtin_unset(input, envp);
		if (ft_strncmp(input, "cd", 2) == 0)
			envp = builtin_cd(ft_split(input, ' '), envp);
		if (ft_strncmp(input, "export", 6) == 0)
			envp = builtin_export(ft_split(input, ' '), envp);
		free(input);
	}
	return (0);
}
