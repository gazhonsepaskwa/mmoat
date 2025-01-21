#include "../includes/minishell.h" 

char	*powerline(void)
{
	char	*pwd;
	char	*tilt;
	char	*input;

	pwd = getcwd(NULL, 0);
	if (ft_strncmp(pwd, "/home/", 6) == 0)
	{
		pwd = pwd + 6;
		while (*pwd && (*pwd) != '/')
			pwd = pwd + 1;
		tilt = " ~";
	}
	else
		tilt = " ";
	printf("%s----------------------------------------------\
----------------------------------%s", POW5, RESET);
	printf("\n%s   MMOAT %s%s%s%s%s %s%s%s ",
		POW1, POW2, POW3, POW4, tilt, pwd, RESET, POW5, RESET);
	input = readline("");
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
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

static t_data	*init_data(char **envp)
{
	t_data	*data;

	data = malloc (sizeof(t_data));
	data->env = init_env(envp);
	return (data);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)ac;
	(void)av;
	// if (!envp[0])
	// 	env = ft_setnewenv();
	data = init_data(envp);
	while (1)
	{
		input = powerline();
		if (ft_strncmp(input, "exit", 4) == 0)
			builtin_exit(input, true);
		if (ft_strncmp(input, "pwd", 3) == 0)
			builtin_pwd(input);
		if (ft_strncmp(input, "echo", 4) == 0)
			builtin_echo(ft_split(input, " "), data->env);
		if (ft_strncmp(input, "env", 3) == 0)
			builtin_env(input, data->env);
		if (ft_strncmp(input, "unset", 5) == 0)
			builtin_unset(ft_split(input, " "), data);
		if (ft_strncmp(input, "cd", 2) == 0)
			builtin_cd(ft_split(input, " "), data);
		if (ft_strncmp(input, "export", 6) == 0)
			builtin_export(ft_split(input, " "), data);
		free(input);
	}
	return (0);
}
