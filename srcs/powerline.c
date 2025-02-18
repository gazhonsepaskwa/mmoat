/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:19:10 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:51 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/ioctl.h>

static void	handle_input(char *in, t_msh *msh)
{
	if (ft_strlen(in) > 0 && !is_only_space(in))
	{
		if (ft_strlen(in) != ft_strlen(msh->prev_input) ||
			ft_strncmp(in, msh->prev_input, -1) != 0)
		{
			add_history(in);
			ft_fprintf(msh->hist, "%s\n", in);
		}
	}
	ft_free(&msh->prev_input);
	if (in)
		msh->prev_input = ft_strdup(in);
}

char	*get_pwd(void)
{
	char	*pwd;
	char	*pwd_base;
	char	*cpy;
	char	*out;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_strdup(""));
	pwd_base = pwd;
	cpy = pwd;
	if (ft_strncmp(pwd, "/home/", 6) == 0)
	{
		pwd += 6;
		while (pwd && *pwd && (*pwd) != '/')
			pwd++;
		out = ft_strjoin("~", pwd);
	}
	else
	{
		out = ft_strdup(cpy);
	}
	free(pwd_base);
	return (out);
}

char	*powerline(t_msh *msh)
{
	char			*pwd;
	char			*input;
	char			*prompt;
	char			*separator;
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	pwd = get_pwd();
	separator = rep_c('-', w.ws_col);
	prompt = ft_sprintf("%s%s%s\n%s   MMOAT %s%s %s%s %s%s%s ",
			SEP, separator, RESET, POW1, POW2, POW3,
			POW4, pwd, RESET, POW5, RESET);
	input = readline(prompt);
	handle_input(input, msh);
	free(separator);
	free(prompt);
	free(pwd);
	return (input);
}
