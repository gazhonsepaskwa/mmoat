#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h> 
# include <stdlib.h> 
# include <stdbool.h>

# include "../lib/libft/libft.h"
# include "builtins.h"
# include "env.h"

# define POW1 "\033[1;38;2;21;22;26;48;2;92;106;178m"
# define POW2 "\033[1;38;2;92;106;178;48;2;54;54;54m"
# define POW3 "\033[1;38;2;54;54;54;48;2;39;39;39m"
# define POW4 "\033[0;38;2;204;205;209;48;2;39;39;39m"
# define POW5 "\033[1;38;2;39;39;39m"

#endif
