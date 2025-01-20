#include "../../includes/builtins.h"

void	pwd_update(t_data *data, char *src, char *dest)
{
	set_var_env("OLDPWD", src, data);
	set_var_env("PWD", dest, data);
	free_null_ptr(src);
	free_null_ptr(dest);
}

int	exec_cd(char *path, t_data *data)
{
	char	*src;
	char	*dest;

	src = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (err_msg_cmd("cd", path, strerror(errno), EXIT_FAILURE));
	dest = getcwd(NULL, 0);
	pwd_update(data, src, dest);
	return (0);
}

int	builtin_cd(char **arg, t_data *data)
{
	char	*path;

	if (count_var(arg) == 1 || (count_var(arg) == 2 && ft_strncmp(arg[1], "~", 1) == 0))
	{
		path = get_var_value("HOME", data->env);
		if (!path)
			return (err_msg_cmd("cd", NULL, "HOME not set\n", EXIT_FAILURE));
		return (exec_cd(path, data));
	}
	if (count_var(arg) > 2)
		return (err_msg_cmd("cd", NULL, "too many arguments\n", EXIT_FAILURE));
	if (ft_strncmp(arg[1], "-", 1) == 0)
	{
		path = get_var_value("OLDPWD", data->env);
		if (!path)
			return (err_msg_cmd("cd", NULL, "OLDPWD not set\n", EXIT_FAILURE));
		return (exec_cd(path, data));
	}
	return (exec_cd(arg[1], data));
}
