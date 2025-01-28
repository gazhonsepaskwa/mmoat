/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:22:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 15:39:37 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_file(t_ast_n *node, int check)
{
	int	fd;

	if (check == 1)
		fd = open(node->infile, O_RDONLY);
	else if (check == 2)
		fd = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (check == 3)
		fd = open(node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	if (check == 1)
		node->_stdin = fd;
	else if (check == 2 || check == 3)
		node->_stdout = fd;
}

void	handle_redir(t_ast_n *node)
{
	if (node->redir == _NR)
		return ;
	else if (node->redir == _RED_L)
		handle_file(node, 1);
	else if (node->redir == _RED_R)
		handle_file(node, 2);
	else if (node->redir == _RED_DR)
		handle_file(node, 3);
	if (node->redir == _RED_L)
	{
		dup2(node->_stdin, STDIN_FILENO);
		close(node->_stdin);
	}
	else if (node->redir == _RED_R || node->redir == _RED_DR)
	{
		dup2(node->_stdout, STDOUT_FILENO);
		close(node->_stdout);
	}
}


int	is_builtin(char *str)
{
	if (ft_strncmp(str, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (1);
	else
		return (0);
}

int	exec_builtin(t_ast_n *node)
{
	handle_redir(node);
	if (ft_strncmp(node->cmd, "exit", 4) == 0)
		return (builtin_exit(node->args, true));
	else if (ft_strncmp(node->cmd, "pwd", 3) == 0)
		return (builtin_pwd(node->args));
	else if (ft_strncmp(node->cmd, "echo", 4) == 0)
		return (builtin_echo(node->args, node->head->env));
	else if (ft_strncmp(node->cmd, "env", 3) == 0)
		return (builtin_env(node->args, node->head->env));
	else if (ft_strncmp(node->cmd, "unset", 5) == 0)
		return (builtin_unset(node->args, node->head));
	else if (ft_strncmp(node->cmd, "cd", 2) == 0)
		return (builtin_cd(node->args, node->head));
	else 
		return (builtin_export(node->args, node->head));
}

char	*find_path(char *cmd, char **env)
{
	char	*tmp;
	char	*path;
	char	**paths;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (free_tab(paths), path);
		free(path);
	}
	free_tab(paths);
	return (NULL);
}

void	return_error(char *arg, char *msg, int code)
{
	ft_fprintf(2, "%s: %s\n", arg, msg);
	exit(code);
}

int	exec(t_ast_n *node)
{
	char	*path;

	handle_redir(node);
	path = find_path(node->cmd, node->head->env);
	if (!path)
		return_error(node->cmd, "command not found", 127);
	if (access(path, X_OK) != 0)
	{
		free(path);
		return_error(path, "Permission denied", 126);
	}
	execve(path, node->args, NULL);
	free(path);
	perror("execve");
	exit(1);
}

int	exec_scmd(t_ast_n *node)
{
	pid_t	pid;
	int		status;

	if (is_builtin(node->cmd))
		return (exec_builtin(node));
	else
	{
		pid = fork();
		if (pid == 0)
			exec(node);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else
				return (-1);
		}
		return (1);
	}
}

// int	exec_pipe(t_ast_n **pline)
// {
// 	int		i;
// 	pid_t	pid;
//
// 	i = -1;
// 	while (pline[++i])
// 	{
// 		pipe(pline[i]->fds);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(pline[i]->fds[0]);
// 			dup2(pline[i]->fds[1], STDOUT_FILENO);
// 			close(pline[i]->fds[1]);
// 			execute_command(pline[i]);
// 		}
// 		else
// 		{
// 			close(pline[i]->fds[1]);
// 			dup2(pline[i]->fds[0], STDIN_FILENO);
// 			close(pline[i]->fds[0]);
// 		}
// 	}
// }

int	execute_command(t_ast_n *node)
{
	int	status;

	if (node->state == _CMD)
		return (exec_scmd(node));
	else if (node->state == _AND)
	{
		status = execute_command(node->left);
		if (status == 0)
			return (execute_command(node->right));
		return (status);
	}
	else if (node->state == _OR)
	{
		status = execute_command(node->left);
		if (status != 0)
			return (execute_command(node->right));
		return (status);
	}
	// else if (node->state == _PLINE)
	// 	return (exec_pipe(node->pline));
	return (0);
}
