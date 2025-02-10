/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:22:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/10 10:31:33 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <time.h>
// #include <unistd.h>

void	handle_file(t_ast_n *node, int check, int i)
{
	int	fd;

	if (check == 1)
		fd = open(node->files[i], O_RDONLY);
	else if (check == 2)
		fd = open(node->files[i], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (check == 3)
		fd = open(node->files[i], O_WRONLY | O_CREAT | O_APPEND, 0666);
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

void	read_input(t_ast_n *node, int j)
{
	char	buf[100000];
	char	c;
	int		r;
	int		i;

	r = 0;
	i = 0;
	ft_fprintf(2, "heredoc> ");
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[i++] = c;
		r = read(STDIN_FILENO, &c, 1);
	}
	buf[i] = '\0';
	if (ft_strncmp(buf, node->files[j], ft_strlen(node->files[j])) == 0)
	{
		close(node->fds[1]);
		exit(EXIT_SUCCESS);
	}
	buf[i++] = '\n';
	buf[i] = '\0';
	ft_fprintf(node->fds[1], "%s", buf);
}

void	here_doc(t_ast_n *node, int i)
{
	pid_t	pid;
	int		fd;

	pipe(node->fds);
	pid = fork();
	if (pid == 0)
	{
		fd = open("/dev/tty", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		close(node->fds[0]);
		while (1)
			read_input(node, i);
	}
	else if (pid > 0)
	{
		close(node->fds[1]);
		dup2(node->fds[0], STDIN_FILENO);
		close(node->fds[0]);
		waitpid(pid, NULL, 0);
	}
	else if (pid < 0)
		exit (err_msg_cmd("fork", NULL, "failed to fork", 1));
}

void	save_stds(t_ast_n *node)
{
	node->save_stdo = dup(STDOUT_FILENO);
	node->save_stdi = dup(STDIN_FILENO);
}

void	handle_redir(t_ast_n *node)
{
	int	i;

	i = -1;
	if (node->state == _PLINE || node->redir[0] != _NR)
		save_stds(node);
	while (node->state != _PLINE && node->redir[++i] && node->redir[i] != _NR)
	{
		if (node->redir[i] == _RED_L)
			handle_file(node, 1, i);
		else if (node->redir[i] == _RED_R)
			handle_file(node, 2, i);
		else if (node->redir[i] == _RED_DR)
			handle_file(node, 3, i);
		// else if (node->redir[i] == _RED_DL)
		// 	here_doc(node, i);
		if (node->redir[i] == _RED_L)
		{
			dup2(node->_stdin, STDIN_FILENO);
			close(node->_stdin);
		}
		else if (node->redir[i] == _RED_R || node->redir[i] == _RED_DR)
		{
			dup2(node->_stdout, STDOUT_FILENO);
			close(node->_stdout);
		}
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

void	reset_redir(t_ast_n *node)
{
	if (node->state == _PLINE || node->redir[0] != _NR)
	{
		dup2(node->save_stdo, STDOUT_FILENO);
		close(node->save_stdo);
		dup2(node->save_stdi, STDIN_FILENO);
		close(node->save_stdi);
	}
}

int	exec_builtin(t_ast_n *node)
{
	int	ret;

	expand_node(node);
	if (ft_strncmp(node->cmd, "exit", 4) == 0)
		ret = builtin_exit(node->args, node->sh, node);
	else if (ft_strncmp(node->cmd, "pwd", 3) == 0)
		ret = builtin_pwd(node->args);
	else if (ft_strncmp(node->cmd, "echo", 4) == 0)
		ret = builtin_echo(node, node->msh->env);
	else if (ft_strncmp(node->cmd, "env", 3) == 0)
		ret = builtin_env(node->args, node->msh->env);
	else if (ft_strncmp(node->cmd, "unset", 5) == 0)
		ret = builtin_unset(node->args, node);
	else if (ft_strncmp(node->cmd, "cd", 2) == 0)
		ret = builtin_cd(node->args, node);
	else
		ret = builtin_export(node->args, node);
	return (ret);
}

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
	char	*tmp;
	char	*path;
	char	**paths;
	int		i;

	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
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
	free(arg);
	exit(code);
}

int	exec(t_ast_n *node)
{
	char	*path;

	expand_node(node);
	path = find_path(node->cmd, node->msh->env);
	if (!path)
		return_error(node->cmd, "command not found", 127);
	if (access(path, X_OK) != 0)
		return_error(path, "Permission denied", 126);
	execve(path, node->args, node->msh->env);
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

int	err_fork_pline(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
	perror("fork");
	return (1);
}

void	exec_pcmd(t_ast_n *pcmd)
{
	int	ret;

	if (!pcmd->cmd)
		exit(0);
	if (is_builtin(pcmd->cmd))
	{
		ret = exec_builtin(pcmd);
		free_child(pcmd->msh);
		exit(ret);
	}
	else
		exec(pcmd);
}

int	exec_subsh(t_ast_n *node);
int	execute_shcommand(t_ast_n *node);

void	exec_pchild(int *pipes, int index, t_ast_n *pcmd, int cmds)
{
	int	ret;

	ret = 0;
	if (index < cmds - 1)
		dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	close(pipes[1]);
	handle_redir(pcmd);
	if (pcmd->state == _CMD)
		exec_pcmd(pcmd);
	else if (pcmd->state == _SUBSH)
	{
		ret = execute_shcommand(pcmd->left);
		free_child(pcmd->msh);
		exit(ret);
	}
}

int	end_pline(pid_t last_pid, t_ast_n **pline)
{
	int	status;
	int	i;

	i = -1;
	waitpid(last_pid, &status, 0);
	while (++i < count_cmds(pline) - 1)
		wait(NULL);
	reset_redir(pline[0]->parent);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int	exec_pline(t_ast_n **pline)
{
	int		i;
	pid_t	pid;
	pid_t	last_pid;

	i = -1;
	while (pline[++i])
	{
		if (i == 0)
			handle_redir(pline[0]->parent);
		pipe(pline[i]->fds);
		pid = fork();
		if (pid == 0)
			exec_pchild(pline[i]->fds, i, pline[i], count_cmds(pline));
		else if (pid > 0)
		{
			dup2(pline[i]->fds[0], STDIN_FILENO);
			close(pline[i]->fds[0]);
			close(pline[i]->fds[1]);
			if (i == count_cmds(pline) - 1)
				last_pid = pid;
		}
		else if (pid < 0)
			return (err_fork_pline(pline[i]->fds));
	}
	return (end_pline(last_pid, pline));
}

int	exec_shcmd(t_ast_n *node)
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

int	exec_subsh(t_ast_n *node);

int	execute_shcommand(t_ast_n *node)
{
	if (node->state == _CMD)
		handle_redir(node);
	if (node->state == _CMD)
		node->msh->ex_code = exec_shcmd(node);
	else if (node->state == _AND)
	{
		node->msh->ex_code = execute_shcommand(node->left);
		if (node->msh->ex_code == 0)
			node->msh->ex_code = execute_shcommand(node->right);
	}
	else if (node->state == _OR)
	{
		node->msh->ex_code = execute_shcommand(node->left);
		if (node->msh->ex_code != 0)
			node->msh->ex_code = execute_shcommand(node->right);
	}
	else if (node->state == _PLINE)
		node->msh->ex_code = exec_pline(node->pline);
	else if (node->state == _SUBSH)
		node->msh->ex_code = exec_subsh(node->left);
	if (node->state == _CMD)
		reset_redir(node);
	return (node->msh->ex_code);
}

int	exec_subsh(t_ast_n *node)
{
	int		status;
	pid_t	pid;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		handle_redir(node->parent);
		ret = execute_shcommand(node);
		// reset_redir(node->parent);
		free_child(node->msh);
		exit(ret);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && node->parent->state != _PLINE)
			return (WEXITSTATUS(status));
		else
			return (1);
	}
	else
	{
		perror("fork");
		return (1);
	}
}

int	execute_command(t_ast_n *node)
{
	if (node->state == _CMD)
		handle_redir(node);
	if (node->state == _CMD)
		node->msh->ex_code = exec_scmd(node);
	else if (node->state == _AND)
	{
		node->msh->ex_code = execute_command(node->left);
		if (node->msh->ex_code == 0)
			node->msh->ex_code = execute_command(node->right);
	}
	else if (node->state == _OR)
	{
		node->msh->ex_code = execute_command(node->left);
		if (node->msh->ex_code != 0)
			node->msh->ex_code = execute_command(node->right);
	}
	else if (node->state == _PLINE)
		node->msh->ex_code = exec_pline(node->pline);
	else if (node->state == _SUBSH)
		node->msh->ex_code = exec_subsh(node->left);
	if (node->state == _CMD)
		reset_redir(node);
	return (node->msh->ex_code);
}
