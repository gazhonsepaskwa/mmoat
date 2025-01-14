#ifndef BUILTINS_H
# define BUILTINS_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>
# include <errno.h>

// void 	echo(char *msg, int flag);
void	builtin_exit(char *arg, bool depth);
void	builtin_pwd(char *arg);


#endif
