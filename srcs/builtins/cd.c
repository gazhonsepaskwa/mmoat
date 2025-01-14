#include "../../includes/builtins.h"

// static char	*find_home(char **envp)
// {
// 	int		i;
// 	char	*str;
//
// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (ft_strnstr(envp[i], "HOME=", 5) == 0)
// 		i++;
// 	str = envp[i + 5];
// 	return (str);
// }
//
// int	cd(char *path, char **envp)
// {
// 	char	*str;
//
// 	if (path == NULL)
// 	{
// 		//cd $HOME
// 		str = find_home(envp);
// 		chdir(str);
// 	}	
// }
