#include "../../includes/builtins.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

void	bash_exit(int code)
{
	ft_putendl_fd("exit", 2);
	exit(code);
}

void	bash_exit_error(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_put_s_fd("minishell: exit: ", 2);
	write(2, arg, ft_strlen(arg));
	ft_putendl_fd(": numeric argument required", 2);
	exit(2);
}

void	builtin_exit(char *arg, bool depth)
{
	if (depth == true)
	{
		if (!ft_isnumeric(arg))
		{
			ft_put_s_fd("minishell: exit: ", 2);
			write(2, arg, ft_strlen(arg));
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		exit(ft_atoi(arg));
	}
	if (ft_isnumeric(arg))
		bash_exit(ft_atoi(arg));
	else
		bash_exit_error(arg);
}
