/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:00:08 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:31:03 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>

int	count_cmds(t_ast_n **pline)
{
	int	i;

	i = 0;
	if (!pline || !*pline)
		return (0);
	while (pline[i])
		i++;
	return (i);
}

char	*find_path(char *cmd, char **env)
{
	char		*tmp;
	char		*path;
	char		**paths;
	int			i;

	if (access(cmd, F_OK) == 0 && !is_dir(cmd) && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(env[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0 && !is_dir(path))
			return (free_tab(paths), path);
		free(path);
	}
	return (free_tab(paths), NULL);
}

void	return_error(char *arg, char *msg, int code, t_ast_n *node)
{
	ft_fprintf(2, "%s: %s\n", arg, msg);
	free_child(node->msh);
	exit(code);
}

int	exec(t_ast_n *node)
{
	char	*path;

	expand_node(node);
	if (node->msh->here_fd != -1)
		close(node->msh->here_fd);
	if (node->msh->hist != -1)
		close(node->msh->hist);
	path = find_path(node->cmd, node->msh->env);
	if (!path)
	{
		if (!access(node->cmd, F_OK) && access(node->cmd, X_OK))
			return_error(node->cmd, "Permission denied", 126, node);
		else
			return_error(node->cmd, "command not found", 127, node);
	}
	if (access(path, X_OK) != 0)
		return_error(path, "Permission denied", 126, node);
	if (execve(path, node->args, node->msh->env) == -1)
	{
		free_child(node->msh);
		ft_free(&path);
		perror("execve");
		exit(1);
	}
	return (0);
}

int	exec_scmd(t_ast_n *node)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!node->cmd)
		return (0);
	else if (is_builtin(node->cmd))
		return (exec_builtin(node));
	else
	{
		pid = fork();
		if (pid == 0)
			exec(node);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else
				return (1);
		}
		else
			perror("fork");
		return (1);
	}
}
