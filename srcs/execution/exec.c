/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:22:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/27 15:43:24 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	is_builtin(char *str)
// {
// 	if (ft_strncmp(str, "exit", 4) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "pwd", 3) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "echo", 4) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "env", 3) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "unset", 5) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "cd", 2) == 0)
// 		return (1);
// 	if (ft_strncmp(str, "export", 6) == 0)
// 		return (1);
// }

// int	exec_builtin(t_ast_n *node)
// {
// 	if (ft_strncmp(node->cmd, "exit", 4) == 0)
// 		return (builtin_exit(node->cmd, true));
// 	if (ft_strncmp(node->cmd, "pwd", 3) == 0)
// 		return (builtin_pwd(node->cmd));
// 	if (ft_strncmp(node->cmd, "echo", 4) == 0)
// 		return (builtin_echo(ft_split(node->arg, " "), node->head->env));
// 	if (ft_strncmp(node->cmd, "env", 3) == 0)
// 		return (builtin_env(node->cmd, node->head->env));
// 	if (ft_strncmp(node->cmd, "unset", 5) == 0)
// 		return (builtin_unset(ft_split(node->arg, " "), node->head));
// 	if (ft_strncmp(node->cmd, "cd", 2) == 0)
// 		return (builtin_cd(ft_split(node->arg, " "), node->head));
// 	if (ft_strncmp(node->cmd, "export", 6) == 0)
// 		return (builtin_export(ft_split(node->arg, " "), node->head));
// }

// void	free_tab(char **tab)
// {
// 	int	i;
//
// 	i = -1;
// 	while (tab[++i])
// 		free(tab[i]);
// 	free(tab);
// }

char	*find_path(char *cmd, char **env)
{
	char	*tmp;
	char	*path;
	char	**paths;
	int		i;

	// if (access(cmd, F_OK) == 0)
	// 	return (cmd);
	i = 0;
	ft_printf("test2\n");
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(env[i] + 5, ":");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		printf("path: %s\n", path);
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
		handle_file(node , 2);
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

int	exec(t_ast_n *node)
{
	char	*path;

	handle_redir(node);
	ft_printf("test1\n");
	path = find_path(node->cmd, node->head->env);
	ft_printf("test3\n");
		printf("path: %s\n", path);
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

	// if (is_builtin(node->cmd))
	// 	return (exec_builtin(node));
	// else
	// {
		pid = fork();
		if (pid == 0)
		{
			exec(node);
		}
		else
		{
			wait(NULL);
		return (0);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
			else
				return (-1);
		}
		return (0);
	// }
}

int	execute_command(t_ast_n *node)
{
	int	status;

		printf("test100\n");
	if (node->state == _CMD)
		return (exec_scmd(node));
	else if (node->state == _AND)
	{
		status = execute_command(node->left);
		if (WEXITSTATUS(status) == 0)
			return (execute_command(node->right));
		return (status);
	}
	else if (node->state == _OR)
	{
		status = execute_command(node->left);
		if (WEXITSTATUS(status) != 0)
			return (execute_command(node->right));
		return (status);
	}
	return (0);
	// else if (node->state == _PLINE)
	// 	return (exec_pipe(node));
}
