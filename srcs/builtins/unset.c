#include "../../includes/builtins.h"

// void	builtin_unset(char *str, char **envp)
// {
// 	int		i;
// 	char	*var;
//
// 	if (count_char(str) == 5)
// 	{
// 		ft_putendl_fd("unset: not enough arguments", 2);
// 		// exit(1);
// 	}
// 	i = 0;
// 	while(str[5 + i] && str[5 + i] == ' ')
// 		i++;
// 	var = &str[5 + i];
// 	i = 0;
// 	while (ft_strnstr(envp[i], var, ft_strlen(var)) == NULL)
// 		i++;
// 	if (envp[i])
// 		envp[i][0] = '\0';
// }
//
int	builtin_unset(char **arg, t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	if (count_var(arg) == 1)
		return (err_msg_cmd("unset", NULL, "not enough arguments", EXIT_FAILURE));
	while (++i < count_var(arg))
		ret = remove_env_var(arg[i], data);	
	return (ret);
}
