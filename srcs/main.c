/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:16:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:44:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

int	g_sig = 0;

static void	add_prevhistory(t_msh *msh)
{
	char	*str;
	char	*tmp;

	str = get_next_line(msh->hist, 0);
	while (str)
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_free(&msh->prev_input);
		msh->prev_input = ft_strdup(tmp);
		add_history(tmp);
		free(tmp);
		free(str);
		str = get_next_line(msh->hist, 0);
	}
}

void	handle_sigint(int sig)
{
	(void)sig;
	int	status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (pid > 0 && (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT))
	{
		write(2, "\n", 2);
	}
	else
	{
		write(2, "\n\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_sig = sig;
}

static void	exit_manual(t_msh *msh)
{
	int	ret;

	if (g_sig == SIGINT)
	{
		ret = 130;
		g_sig = 0;
	}
	else
		ret = msh->ex_code;
	ft_free(&msh->prev_input);
	free_msh(msh);
	ft_fprintf(2, "exit\n");
	exit(ret);
}

int	interactive_mode(t_msh *msh)
{
	msh->input = malloc(1);
	msh->input[0] = 0;
	while (!msh->input[0] || is_only_space(msh->input))
	{
		free(msh->input);
		msh->input = powerline(msh);
		if (!msh->input)
			exit_manual(msh);
	}
	if (!msh->input)
		return (1);
	if (g_sig == SIGINT)
	{
		msh->ex_code = 130;
		g_sig = 0;
	}
	interpret_cmd(&msh->input, msh);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_msh			*msh;
	struct termios	term;

	(void)av;
	tcgetattr(STDIN_FILENO, &term);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	msh = init_msh(envp);
	init_sig();
	add_prevhistory(msh);
	if (!msh)
		return (1);
	if (ac == 1)
	{
		while (1)
			if (!interactive_mode(msh))
				break ;
	}
	else
		ft_error("minishell : usages : - ./minishell\n");
	free_msh(msh);
}
