#include "../../includes/builtins.h"

void	builtin_env(char *str, char **envp)
{
	int	i;

	i = 0;
	(void)str;
	while (envp[i])
	{
		if (envp[i][0])
			printf("%s\n", envp[i]);
		i++;
	}
}
