#ifndef ENV_H
# define ENV_H

# include "../lib/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_data
{
	char **env;
}	t_data;

//VAR
int		count_var(char **envp);
int		get_var_index(char *key, char **envp);
void	free_null_ptr(void *ptr);
char	**copy_env_var(char **envp, int count);
char	*get_var_value(char	*key, char **envp);
bool	is_valid_key(char *key, char **envp);
int		remove_env_var(char *key, char **envp);
void	set_var_env(char *key, char *value, t_data *t_data);

#endif
