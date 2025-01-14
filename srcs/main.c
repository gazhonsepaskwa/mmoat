#include "../includes/minishell.h" 

char	*powerline(void)
{
	char	*pwd;
	char	*tilt;

	pwd = getenv("PWD");
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

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	while (1)
	{
		input = powerline();
		if (ft_strncmp(input, "exit", 4) == 0)
			builtin_exit(&input[5], true);
		if (ft_strncmp(input, "pwd", 3) == 0)
			builtin_pwd(input);
		free(input);
	}
	return (0);
}
