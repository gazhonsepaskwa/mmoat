/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:16:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/08 14:46:35 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 
#include <readline/history.h>

static	void	handle_input(char *in, char *li, char *pr, t_msh *msh)
{
	if (ft_strlen(in) > 0 && !is_only_space(in))
	{
		add_history(in);
		ft_fprintf(msh->hist, "%s\n", in);
	}
	free(pr);
	free(li);
}

static char	*powerline(t_msh *msh)
{
	char	*pwd;
	char	*tilt;
	char	*input;
	char	*prompt;
	char	*line;

	pwd = getcwd(NULL, 0);
	tilt = " ";
	if (ft_strncmp(pwd, "/home/", 6) == 0)
	{
		pwd += 6;
		while (*pwd && (*pwd) != '/')
			pwd ++;
		tilt = " ~";
	}
	line = ft_sprintf("%s----------------------------------------------\
----------------------------------%s", POW5, RESET);
	prompt = ft_sprintf("%s\n%s   MMOAT %s%s%s%s%s %s%s%s ",
		line, POW1, POW2, POW3, POW4, tilt, pwd, RESET, POW5, RESET);
	input = readline(prompt);
	handle_input(input, line, prompt, msh);
	return (input);
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
	msh->ex_code = execute_command(msh->head);
	free_ast(msh->head);
	msh->head = NULL;
	ft_free(input);
}

int	main(int ac, char **av, char **envp)
{
	t_msh	*msh;

	(void)ac;
	(void)av;
	msh = init_msh(envp);
	add_prevhistory(msh);
	if (!msh)
		return (1);
	if (ac == 1)
	{
		while (1)
		{
			while (!msh->input || !msh->input[0] || is_only_space(msh->input))
				msh->input = powerline(msh);
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
