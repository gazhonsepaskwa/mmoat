#include "../../includes/builtins.h"

void	check_format(char **arg)
{
	(void)arg;
}

void	print_error(char *str, int *code)
{
	ft_put_s_fd("minishell: export: ", 2);
	ft_put_s_fd(str, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	*code = 1;
}

void	print_arr(char **envp)
{
	int		i;
	char	*equal;

	(void)equal;
	i = -1;
	while (envp[++i])
	{
			ft_printf("declare -x %s\n", envp[i]);
	}
}

void	print_export(char **envp)
{
	int		i;
	int		j;
	char	*tmp;
	int		len;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	print_arr(envp);
}

char	**builtin_export(char **arg, char **envp)
{
	char	**new_envp;
	int		i;
	// int		code;

	i =0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 1);
	new_envp[i] = NULL;
	i = -1;
	while (envp[++i])
		new_envp[i] = ft_strdup(envp[i]);
	// code = 0;
	i = 0;
	while (arg[i])
		i++;
	if (i == 1)
		return(print_export(new_envp), envp);
	return (envp);
	// i = -1;
	// while (arg[++i])
	// {
	// 	if (check_format(arg[i]))
	// 	{
	//
	// 	}
	// 	else
	// 		print_error(arg[i], &code);
	// }
}
