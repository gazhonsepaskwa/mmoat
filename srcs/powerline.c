/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:19:10 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/10 12:19:10 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*powerline(t_msh *msh)
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
