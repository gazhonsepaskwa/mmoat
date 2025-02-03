/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:01:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/03 13:03:14 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

# define EXPRT_INV "not a valid identifier"
// void 	echo(char *msg, int flag);
int		builtin_echo(char **arg, char **envp);
int		builtin_exit(char **arg, bool depth);
int		builtin_pwd(char **arg);
int		builtin_env(char **arg, char **envp);
int	builtin_unset(char **arg, t_ast_n *head);
int	builtin_cd(char **arg, t_ast_n *head);
int	builtin_export(char **arg, t_ast_n *head);

//UTILS
int	count_char(char *str);
int	count_args(char **tab);
int	extractenv(char *str, char **envp);
char	*ft_getenv(char *str, char **envp);
int	err_msg_cmd(char *cmd, char *arg, char *msg, int code);

#endif
