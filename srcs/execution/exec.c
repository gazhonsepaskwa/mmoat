/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:22:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 12:30:00 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

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

static int is_validchar(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	get_var_len(char *str, t_ast_n *node, int *j)
{
	int	len;
	int	ret;
	char *var;

	len = *j + 1;
	while (str[len] && is_validchar(str[len]))
		len++;
	var = ft_substr(str, *j + 1, (size_t)len - (*j + 1));
	*j = len;
	ret = ft_strlen(get_var_value(var, node->msh->env));
	ft_free(&var);
	return (ret - (len - (*j + 1)));
}

int get_dup_len(char *str, t_ast_n *node)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			len += get_var_len(str, node, &i);
			i--;
		}
		i++;
	}
	return (len);
}

static int	valid_next(char c)
{
	if (c != '\0' && is_validchar(c))
		return (1);
	return (0);
}

static char	*extract_env(char *str, char **envp)
{
	int		i;
	char	*var;
	char	*tmp;

	i = 1;
	while (str[i] && is_validchar(str[i]))
		i++;
	if (i > 1)
		tmp = ft_substr(str, 1, i - 1);
	var = get_var_value(tmp, envp);
	ft_free(&tmp);
	return (var);
}

void	expander_here(char **str, t_ast_n *node)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = -1;
	len = get_dup_len(*str, node);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return ;
	j = 0;
	while ((*str)[j] && ++i < len)
	{
		if ((*str)[j] != '$')
			new[i] = (*str)[j++];
		else if ((*str)[j] == '$' && valid_next((*str)[j + 1]))
		{
			ft_strlcat(new, extract_env(&((*str)[j]), node->msh->env), -1);
			i = ft_strlen(new) - 1;
			while ((*str)[++j] && is_validchar((*str)[j]))
				continue ;
		}
	}
	ft_free(str);
	*str = new;
}

void	here_remove_quote(t_ast_n *node, int j, char c)
{
	char	*new;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(node->files[j]);
	new = ft_calloc(len - 1, sizeof(char));
	while (i < len - 2)
	{
		if ((&(node->files[j][k]) == ft_strchr(node->files[j], c)) ||
	  		(&(node->files[j][k]) == ft_strrchr(node->files[j], c)))
		{
			k++;
		}
		else
			new[i++] = node->files[j][k++];
	}
	ft_free(&node->files[j]);
	node->files[j] = new;
}

int ifhere_remove_quote(t_ast_n *node, int j)
{
	char	c;
	int		ret;
	
	ret = 0;
	if (!ft_strchr(node->files[j], '\'') && !ft_strchr(node->files[j], '\"'))
		c = 0;
	else if (!ft_strchr(node->files[j], '\"'))
		c = '\'';
	else if (!ft_strchr(node->files[j], '\''))
		c = '\"';
	else if (ft_strchr(node->files[j], '\'') < ft_strchr(node->files[j], '\"'))
		c = '\'';
	else
		c = '\"';
	if (c && (ft_strchr(node->files[j], c) != ft_strrchr(node->files[j], c)))
		here_remove_quote(node, j, c);
	if (c)
		ret = 1;
	return (ret);
}

void	read_input(t_ast_n *node, int j)
{
	char	*str;
	int		len;
	int		check;

	check = ifhere_remove_quote(node, j);
	len = ft_strlen(node->files[j]);
	str = get_next_line(node->msh->here_fd, 0);
	while (str && ft_strncmp(str, node->files[j], len) != 0)
	{
		if (!check)
			expander_here(&str, node);
		write(1, str, ft_strlen(str));
		ft_free(&str);
		str = get_next_line(node->msh->here_fd, 0);
	}
	if (!str)
		get_next_line(node->msh->here_fd, 1);
	ft_free(&str);
}

void	here_doc(t_ast_n *node, int i)
{
	pid_t	pid;

	pipe(node->fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(node->fds[1], STDOUT_FILENO);
		close(node->fds[0]);
		close(node->fds[1]);
		read_input(node, i);
		free_child(node->msh);
		exit(EXIT_SUCCESS);
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
		else if (node->redir[i] == _RED_DL)
			here_doc(node, i);
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
	if (ft_strncmp(str, "exit", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "echo", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "env", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", -1) == 0)
		return (1);
	else if (ft_strncmp(str, "export", -1) == 0)
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
	if (ft_strncmp(node->cmd, "exit", -1) == 0)
		ret = builtin_exit(node->args, node->sh, node);
	else if (ft_strncmp(node->cmd, "pwd", -1) == 0)
		ret = builtin_pwd(node->args);
	else if (ft_strncmp(node->cmd, "echo", -1) == 0)
		ret = builtin_echo(node, node->msh->env);
	else if (ft_strncmp(node->cmd, "env", -1) == 0)
		ret = builtin_env(node->args, node->msh->env);
	else if (ft_strncmp(node->cmd, "unset", -1) == 0)
		ret = builtin_unset(node->args, node);
	else if (ft_strncmp(node->cmd, "cd", -1) == 0)
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
		if (access(path, F_OK) == 0)
			return (free_tab(paths), path);
		free(path);
	}
	free_tab(paths);
	return (NULL);
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
	path = find_path(node->cmd, node->msh->env);
	if (!path)
		return_error(node->cmd, "command not found", 127, node);
	if (access(path, X_OK) != 0)
		return_error(path, "Permission denied", 126, node);
	if (execve(path, node->args, node->msh->env) == -1)
	{
		free_child(node->msh);
		perror("execve");
		exit(1);
	}
	return (0);
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
