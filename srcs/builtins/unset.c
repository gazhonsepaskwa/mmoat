#include "../../includes/builtins.h"

void	builtin_unset(char *str, char **envp)
{
	int		i;
	char	*var;

	if (count_char(str) == 5)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		// exit(1);
	}
	i = 0;
	while(str[5 + i] && str[5 + i] == ' ')
		i++;
	var = &str[5 + i];
	i = 0;
	while (ft_strnstr(envp[i], var, ft_strlen(var)) == NULL)
		i++;
	if (envp[i])
		envp[i][0] = '\0';
}
