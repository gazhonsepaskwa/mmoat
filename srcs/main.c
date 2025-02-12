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
	while (!msh->input[0] || is_only_space(msh->input))
	{
		free(msh->input);
		msh->input = powerline(msh);
		if (!msh->input)
			return (0);
	}
	if (!msh->input)
		return (1);
	interpret_cmd(&msh->input, msh);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;
	struct termios term;

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
