#ifndef BUILTINS_H
# define BUILTINS_H

# include "../lib/libft/libft.h"
# include "env.h"
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <string.h>

// void 	echo(char *msg, int flag);
void	builtin_echo(char *arg, char **envp);
void	builtin_exit(char *arg, bool depth);
void	builtin_pwd(char *arg);
void	builtin_env(char *str, char **envp);
int	builtin_unset(char **arg, t_data *data);
int	builtin_cd(char **arg, t_data *data);
char	**builtin_export(char **arg, char **envp);

//UTILS
int	count_char(char *str);
int	count_args(char **tab);
int	extractenv(char *str, char **envp);
char	*ft_getenv(char *str, char **envp);
int	err_msg_cmd(char *cmd, char *arg, char *msg, int code);

#endif
