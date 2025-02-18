/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 09:53:26 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/12 09:53:26 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expander_here(char **str, t_ast_n *node)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = -1;
	len = get_dup_len(*str, node);
	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return ;
	j = 0;
	while ((*str)[j] && ++i < len)
	{
		if ((*str)[j] != '$')
			new[i] = (*str)[j++];
		else if ((*str)[j] == '$' && execvalid_next((*str)[j + 1]))
		{
			ft_strlcat(new, execextract_env(&((*str)[j]), node->msh->env), -1);
			i = ft_strlen(new) - 1;
			while ((*str)[++j] && execis_validchar((*str)[j]))
				continue ;
		}
	}
	ft_free(str);
	*str = new;
}

void	here_remove_quote(t_ast_n *node, int j, char c)
{
	char	*new;
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	len = ft_strlen(node->files[j]);
	new = ft_calloc(len - 1, sizeof(char));
	while (i < len - 2)
	{
		if ((&(node->files[j][k]) == ft_strchr(node->files[j], c)) ||
			(&(node->files[j][k]) == ft_strrchr(node->files[j], c)))
		{
			k++;
		}
		else
			new[i++] = node->files[j][k++];
	}
	ft_free(&node->files[j]);
	node->files[j] = new;
}

int	ifhere_remove_quote(t_ast_n *node, int j)
{
	char	c;
	int		ret;

	ret = 0;
	if (!ft_strchr(node->files[j], '\'') && !ft_strchr(node->files[j], '\"'))
		c = 0;
	else if (!ft_strchr(node->files[j], '\"'))
		c = '\'';
	else if (!ft_strchr(node->files[j], '\''))
		c = '\"';
	else if (ft_strchr(node->files[j], '\'') < ft_strchr(node->files[j], '\"'))
		c = '\'';
	else
		c = '\"';
	if (c && (ft_strchr(node->files[j], c) != ft_strrchr(node->files[j], c)))
		here_remove_quote(node, j, c);
	if (c)
		ret = 1;
	return (ret);
}

void	read_input(t_ast_n *node, int j)
{
	char	*str;
	int		check;

	check = ifhere_remove_quote(node, j);
	str = get_next_line(node->msh->here_fd, 0);
	while (str && ft_strncmp(str, node->files[j], -1) != 0)
	{
		if (!check)
			expander_here(&str, node);
		write(1, str, ft_strlen(str));
		ft_free(&str);
		str = get_next_line(node->msh->here_fd, 0);
	}
	if (!str)
		get_next_line(node->msh->here_fd, 1);
	ft_free(&str);
}

void	here_doc(t_ast_n *node, int i)
{
	pid_t	pid;

	pipe(node->fds);
	pid = fork();
	if (pid == 0)
	{
		dup2(node->fds[1], STDOUT_FILENO);
		close(node->fds[0]);
		close(node->fds[1]);
		read_input(node, i);
		free_child(node->msh);
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		close(node->fds[1]);
		dup2(node->fds[0], STDIN_FILENO);
		close(node->fds[0]);
		waitpid(pid, NULL, 0);
	}
	else if (pid < 0)
		exit (err_msg_cmd("fork", NULL, "failed to fork", 1));
}
