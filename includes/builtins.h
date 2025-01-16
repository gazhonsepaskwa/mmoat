#ifndef BUILTINS_H
# define BUILTINS_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>

// void 	echo(char *msg, int flag);
void	builtin_echo(char *arg, char **envp);
void	builtin_exit(char *arg, bool depth);
void	builtin_pwd(char *arg);
void	builtin_env(char *str, char **envp);
void	builtin_unset(char *str, char **envp);
char	**builtin_cd(char **arg, char **envp);
char	**builtin_export(char **arg, char **envp);

//UTILS
int	count_char(char *str);
#endif
