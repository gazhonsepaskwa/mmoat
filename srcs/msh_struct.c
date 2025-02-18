/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:32:03 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/11 16:34:46 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

static char	**ft_setnewenv(void)
{
	char	**envp;

	envp = malloc(sizeof(char *) * 2);
	if (!envp)
		return (NULL);
	envp[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	envp[1] = ft_strdup("SHLVL=1");
	if (!envp[0] || !envp[1])
		return (ft_free(&envp[0]), ft_free(&envp[1]), NULL);
	return (envp);
}

t_msh	*init_msh(char **envp)
{
	t_msh	*msh;
	int		fd;

	msh = malloc(sizeof(t_msh) * 1);
	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	close(fd);
	msh->hist = open(".mmoat_history", O_RDWR | O_CREAT | O_APPEND, 0666);
	msh->ex_code = 0;
	msh->here_fd = -1;
	msh->input = NULL;
	msh->prev_input = NULL;
	if (!msh)
		return (NULL);
	if (!envp[0])
		msh->env = ft_setnewenv();
	else
		msh->env = init_env(envp);
	return (msh);
}

void	free_msh(t_msh *msh)
{
	free_tab(msh->env);
	if (msh->hist != -1)
		close(msh->hist);
	if (msh->here_fd != -1)
		close(msh->here_fd);
	free(msh->input);
	ft_free(&msh->prev_input);
	free(msh);
}
