/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:50:12 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 13:30:51 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pcmd(t_ast_n *pcmd)
{
	int	ret;

	if (pcmd->msh->here_fd != -1)
		close(pcmd->msh->here_fd);
	close(pcmd->msh->hist);
	if (pcmd->save_stdo != -1)
		close(pcmd->save_stdo);
	if (pcmd->save_stdi != -1)
		close(pcmd->save_stdi);
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

void	exec_pchild(int *pipes, int index, t_ast_n *pcmd, int cmds)
{
	int	ret;

	ret = 0;
	if (index < cmds - 1)
		dup2(pipes[1], STDOUT_FILENO);
	close(pipes[0]);
	close(pipes[1]);
	if (handle_redir(pcmd))
	{
		free_child(pcmd->msh);
		exit(1);
	}
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
