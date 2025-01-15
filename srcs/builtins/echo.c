#include "../../includes/builtins.h"

int	is_silentchar(char c)
{
	if (c == 'n' || c == '-' || c == ' ')
		return (1);
	else
		return (0);
}

int	is_silent(char *str)
{
	int	i;

	i = 4;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i] == '-')
	{
		i++;
		if (str[i] && str[i] == 'n')
			return (1);
	}
	return (0);
}

static int	extractenv(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 0;
	(void)envp;
	while (str[i] && str[i] != ' ')
		i++;
	if (i >= 1)
		tmp = ft_substr(str, 1, i - 1);
	var = getenv(tmp);
	free(tmp);
	if (var)
		ft_printf("%s", var);
	return (i);
}

static void	echo_print(char *str, char **envp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (!str[i + 1] || str[i + 1] == ' ')
				ft_put_c(str[i++]);
			else
				i += extractenv(&str[i], envp);
		}
		else
			ft_put_c(str[i++]);
	}
}

void	builtin_echo(char *arg, char **envp)
{
	int	i;

	i = 4;
	while (arg[i] && is_silentchar(arg[i]))
		i++;
	echo_print(&arg[i], envp);
	if (!is_silent(arg))
		printf("\n");
}
