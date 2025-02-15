/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:01:33 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/05 11:50:47 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_ast_n	t_ast_n;
typedef struct s_node	t_node;
typedef struct s_msh	t_msh;

# define UNSET_ARG "not enough arguments"
# define EXPRT_INV "not a valid identifier"

int		builtin_echo(t_ast_n *node, char **envp);
int		builtin_exit(char **arg, bool depth, t_ast_n *node);
int		builtin_pwd(char **arg);
int		builtin_env(char **arg, char **envp);
int		builtin_unset(char **arg, t_ast_n *head);
int		builtin_cd(char **arg, t_ast_n *head);
int		builtin_export(char **arg, t_ast_n *head);

//UTILS
int		count_char(char *str);
int 	is_append(char *str);
char	**key_value(char *str);
void	set_new_export(char *str, t_ast_n *node);
int		count_args(char **tab);
int		extractenv(char *str, char **envp);
char	*ft_getenv(char *str, char **envp);
int		err_msg_cmd(char *cmd, char *arg, char *msg, int code);
void	char_swap(char **s1, char **s2);

#endif
