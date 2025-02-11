/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:01:14 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 10:45:08 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_quote(char **str, char c)
{
	char	*new;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(*str);
	new = ft_calloc(len - 1, sizeof(char));
	while (i < len - 2)
	{
		if ((&((*str)[k]) == ft_strchr(*str, c)) ||
	  		(&((*str)[k]) == ft_strrchr(*str, c)))
		{
			k++;
		}
		else
			new[i++] = (*str)[k++];
	}
	ft_free(str);
	*str = new;
}

static int ifremove_quote(char **str)
{
	char	c;
	int		ret;
	
	ret = 0;
	if (!ft_strchr(*str, '\'') && !ft_strchr(*str, '\"'))
		c = 0;
	else if (!ft_strchr(*str, '\"'))
		c = '\'';
	else if (!ft_strchr(*str, '\''))
		c = '\"';
	else if (ft_strchr(*str, '\'') < ft_strchr(*str, '\"'))
		c = '\'';
	else
		c = '\"';
	if (c && (ft_strchr(*str, c) != ft_strrchr(*str, c)))
		remove_quote(str, c);
	if (c)
		ret = 1;
	return (ret);
}

void	read_hereinput(char *limiter)
{
	char	buf[100000];
	char	c;
	int		r;
	int		i;

	r = 0;
	i = 0;
	ft_fprintf(2, "heredoc> ");
	r = read(0, &c, 1);
	if (r == 0)
	{
		ft_fprintf (2, "\n");
		ft_fprintf (1, "%s\n", limiter);
		exit(EXIT_SUCCESS);
	}
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[i++] = c;
		r = read(0, &c, 1);
	}
	buf[i] = '\0';
	if (ft_strncmp(buf, limiter, ft_strlen(limiter)) == 0)
	{
		ft_fprintf(1, "%s\n", buf);
		exit(EXIT_SUCCESS);
	}
	buf[i++] = '\n';
	buf[i] = '\0';
	ft_fprintf(1, "%s", buf);
}

void	parse_heredoc(char *limiter)
{
	int	fd;
	pid_t	pid;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0666);
	pid = fork();
	if (pid == 0)
	{
		ifremove_quote(&limiter);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		while (1)
			read_hereinput(limiter);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close (fd);
	}
	else
	{
		close (fd);
		perror("fork");
		exit (EXIT_FAILURE);
	}
}

void	create_heredoc(t_node *lst)
{
	while (lst)
	{
		if (lst->pressision == HEREDOC && lst->next && lst->next->pressision)
		{
			lst = lst->next;
			parse_heredoc(lst->val);
		}
		lst = lst->next;
	}
}
