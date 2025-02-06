/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:32:03 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/06 15:32:03 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_setnewenv(void)
{
	char **envp;

	envp = malloc(sizeof(char *) * 2);
	if (!envp)
		return (NULL);
	envp[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
	envp[1] = ft_strdup("SHLVL=1");
	if (!envp[0] || !envp[1])
		return (ft_free(&envp[0]), ft_free(&envp[1]), NULL);
	return (envp);
}

t_msh *init_msh(char **envp)
{
	t_msh	*msh;

	msh = malloc(sizeof(t_msh) * 1);
	msh->ex_code = 0;
	if (!msh)
		return (NULL);
	if (!envp[0])
		msh->env = ft_setnewenv();
	else
		msh->env = init_env(envp);
	return (msh);
}

void free_msh(t_msh *msh)
{
  free_tab(msh->env);
  free(msh);
}
