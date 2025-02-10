#include "../../includes/minishell.h"

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
		ft_fprintf(1, "%s", buf);
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
