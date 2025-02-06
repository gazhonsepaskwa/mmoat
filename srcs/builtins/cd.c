/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:31:49 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/03 13:12:47 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_update(t_ast_n *head, char *src, char *dest)
{
	set_var_env("OLDPWD", src, head->msh);
	set_var_env("PWD", dest, head->msh);
	free_null_ptr(src);
	free_null_ptr(dest);
}

int	exec_cd(char *path, t_ast_n *head)
{
	char	*src;
	char	*dest;

	src = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (err_msg_cmd("cd", path, strerror(errno), EXIT_FAILURE));
	dest = getcwd(NULL, 0);
	pwd_update(head, src, dest);
	return (0);
}

int	builtin_cd(char **arg, t_ast_n *head)
{
	char	*path;

	if (count_var(arg) == 1 || (count_var(arg) == 2 && ft_strncmp(arg[1], "~", 1) == 0))
	{
		path = get_var_value("HOME", head->msh->env);
		if (!path)
			return (err_msg_cmd("cd", NULL, "HOME not set\n", EXIT_FAILURE));
		return (exec_cd(path, head));
	}
	if (count_var(arg) > 2)
		return (err_msg_cmd("cd", NULL, "too many arguments\n", EXIT_FAILURE));
	if (ft_strncmp(arg[1], "-", 1) == 0)
	{
		path = get_var_value("OLDPWD", head->msh->env);
		if (path)
			ft_printf("%s\n", path);
		if (!path)
			return (err_msg_cmd("cd", NULL, "OLDPWD not set\n", EXIT_FAILURE));
		return (exec_cd(path, head));
	}
	return (exec_cd(arg[1], head));
}
