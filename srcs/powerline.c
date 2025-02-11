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

static void	handle_input(char *in, t_msh *msh)
{
	if (ft_strlen(in) > 0 && !is_only_space(in))
	{
		add_history(in);
		ft_fprintf(msh->hist, "%s\n", in);
	}
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
	char	*pwd;
	char	*input;
	char	*prompt;

	pwd = get_pwd();
	prompt = ft_sprintf("\n%s   MMOAT %s%s %s%s %s%s%s ", POW1, POW2, POW3,
			POW4, pwd, RESET, POW5, RESET);
	input = readline(prompt);
	handle_input(input, msh);
	free(prompt);
	free(pwd);
	return (input);
}
