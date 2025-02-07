/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:16:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/07 09:24:34 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

static char	*powerline(void)
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
	if (ft_strlen(input) > 0)
		add_history(input);
	free(prompt);
	free(line);
	return (input);
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
	if (!msh)
		return (1);
	if (ac == 1)
	{
		while (1)
		{
			while (!msh->input || !msh->input[0] || is_only_space(msh->input))
				msh->input = powerline();
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
