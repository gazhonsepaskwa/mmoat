/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:01:14 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:50 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	remove_quote(char **new, char *limiter, char c)
{
	// char	*new;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(limiter);
	*(new) = ft_calloc(len - 1, sizeof(char));
	while (i < len - 2)
	{
		if ((&(limiter[k]) == ft_strchr(limiter, c))
			|| (&(limiter[k]) == ft_strrchr(limiter, c)))
		{
			k++;
		}
		else
			(*new)[i++] = limiter[k++];
	}
	// ft_free(str);
	// *str = new;
}

static int	ifremove_quote(char **new, char *limiter)
{
	char	c;
	int		ret;

	ret = 0;
	if (!ft_strchr(limiter, '\'') && !ft_strchr(limiter, '\"'))
		c = 0;
	else if (!ft_strchr(limiter, '\"'))
		c = '\'';
	else if (!ft_strchr(limiter, '\''))
		c = '\"';
	else if (ft_strchr(limiter, '\'') < ft_strchr(limiter, '\"'))
		c = '\'';
	else
		c = '\"';
	if (c && (ft_strchr(limiter, c) != ft_strrchr(limiter, c)))
		remove_quote(new, limiter, c);
	else
		*new = ft_strdup(limiter);
	if (c)
		ret = 1;
	return (ret);
}

void	read_hereinput(char *limiter, t_node *lst, t_msh *msh)
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
		exit_heredoc(limiter, msh, lst);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buf[i++] = c;
		r = read(0, &c, 1);
	}
	buf[i] = '\0';
	if (ft_strncmp(buf, limiter, -1) == 0)
		end_heredoc(buf, msh, lst, limiter);
	buf[i++] = '\n';
	buf[i] = '\0';
	ft_fprintf(1, "%s", buf);
}

void	parse_heredoc(char *limiter, t_node *lst, t_msh *msh)
{
	int		fd;
	pid_t	pid;
	char	*new;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0666);
	pid = fork();
	if (pid == 0)
	{
		ifremove_quote(&new, limiter);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		while (1)
			read_hereinput(new, lst, msh);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(fd);
	}
	else
	{
		close(fd);
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

void	create_heredoc(t_node *lst, t_msh *msh)
{
	t_node	*tmp;

	tmp = lst;
	while (lst)
	{
		if (lst->pressision == HEREDOC && lst->next && lst->next->pressision)
		{
			lst = lst->next;
			parse_heredoc(lst->val, tmp, msh);
		}
		lst = lst->next;
	}
}
