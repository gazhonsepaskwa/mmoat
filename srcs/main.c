/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:16:52 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/03 14:19:09 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h" 

char	*powerline(void)
{
	// char	*pwd;
	// char	*tilt;
	char	*input;
	//
	// pwd = getcwd(NULL, 0);
	// if (ft_strncmp(pwd, "/home/", 6) == 0)
	// {
	// 	pwd = pwd + 6;
	// 	while (*pwd && (*pwd) != '/')
	// 		pwd = pwd + 1;
	// 	tilt = " ~";
	// }
	// else
	// 	tilt = " ";
// 	printf("%s----------------------------------------------
//----------------------------------%s", POW5, RESET);
// 	printf("\n%s   MMOAT %s%s%s%s%s %s%s%s ",
// 		POW1, POW2, POW3, POW4, tilt, pwd, RESET, POW5, RESET);
	input = readline(">> ");
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}

char	**ft_setnewenv(void)
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

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_msh	*msh;

	(void)ac;
	(void)av;
	msh = init_msh(envp);
	if (!msh)
		return (1);
	while (1)
	{
		input = powerline();
		msh->head = parser(input, msh);
		msh->ex_code = execute_command(msh->head);
		free(input);
	}
}
