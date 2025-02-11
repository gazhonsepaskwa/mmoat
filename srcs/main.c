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

int			g_sig = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_sig = SIGINT;
	rl_replace_line("", 0);
	// rl_on_new_line();
	rl_done = 1;
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	// ft_printf("\b\b");
}

static void	add_prevhistory(t_msh *msh)
{
	char	*str;
	char	*tmp;

	str = get_next_line(msh->hist, 0);
	while (str)
	{
		tmp = ft_substr(str, 0, ft_strlen(str) - 1);
		add_history(tmp);
		free(tmp);
		free(str);
		str = get_next_line(msh->hist, 0);
	}
}

int	interactive_mode(t_msh *msh)
{
	msh->input = malloc(1);
	msh->input[0] = 0;
	while (!msh->input[0] || is_only_space(msh->input) || g_sig == SIGINT)
	{
		g_sig = 0;
		free(msh->input);
		msh->input = powerline(msh);
		if (!msh->input)
			return (0);
	}
	if (!msh->input)
		return (1);
	if (g_sig != SIGINT)
		interpret_cmd(&msh->input, msh);
	return (1);
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
			if (!interactive_mode(msh))
				break ;
	}
	else
	{
		msh->input = ft_strdup(av[1]);
		interpret_cmd(&msh->input, msh);
	}
	free_msh(msh);
}
