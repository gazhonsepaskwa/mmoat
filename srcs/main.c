/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:16:52 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/10 12:31:46 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include <readline/history.h>
#include <readline/readline.h>

int g_sig = 0;

void handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_replace_line("", 0);
	// rl_on_new_line();
    rl_done = 1;
	rl_redisplay();
}

void handle_sigquit(int sig)
{
	(void)sig;
	// ft_printf("\b\b");
}

static void	add_prevhistory(t_msh *msh)
{
	char	*str;
	char	*tmp;

	str = get_next_line(msh->hist);
	while (str)
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		add_history(tmp);
		free(tmp);
		free(str);
		str = get_next_line(msh->hist);
	}
}

static void	interpret_cmd(char **input, t_msh *msh)
{
	msh->head = parser(*input, msh);
	if (!msh->head)
	{
		ft_free(input);
		return ;
	}
	msh->here_fd = open(".heredoc", O_RDONLY);
	msh->ex_code = execute_command(msh->head);
	close(msh->here_fd);
	unlink(".heredoc");
	free_ast(msh->head);
	msh->head = NULL;
	ft_free(input);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;

	msh = init_msh(envp);
	init_sig();
	add_prevhistory(msh);
	if (!msh)
		return (1);
	if (ac == 1)
	{
		while (1)
		{
			msh->input = malloc (1);
			msh->input[0] = 0;
			while (!msh->input[0] || is_only_space(msh->input) || g_sig == SIGINT)
			{
				g_sig = 0;
				free(msh->input);
				msh->input = powerline(msh);
				if (!msh->input)
					break;
			}
			if (!msh->input)
				break;
			if (g_sig != SIGINT)
				interpret_cmd(&msh->input, msh);
		}
	}
	else
	{
		msh->input = ft_strdup(av[1]);
		interpret_cmd(&msh->input, msh);
	}
	free_msh(msh);
}
