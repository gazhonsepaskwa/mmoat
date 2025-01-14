#include "../../includes/builtins.h"

void	builtin_pwd(char *arg)
{
	char	*cwd;

	if (ft_strlen(arg) > 3)
		ft_putendl_fd("pwd: too many arguments", 2);
	else
	{
		cwd = getcwd(NULL, 4096);
		if (cwd != NULL)
		{
			printf("%s\n", cwd);
			free(cwd);
		}
		if (!cwd)
			perror("pwd");	
	}
}
