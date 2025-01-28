/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:11:07 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/28 10:31:54 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../lib/libft/libft.h"
# include "ast.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

//VAR
int		count_var(char **envp);
int		get_var_index(char *key,  t_ast_n *head);
void	free_null_ptr(void *ptr);
char	**copy_env_var(char **envp, int count);
char	*get_var_value(char	*key, char **envp);
bool	is_valid_key(char *key,  t_ast_n *head);
int		remove_env_var(char *key,  t_ast_n *head);
void	set_var_env(char *key, char *value, t_ast_n *head);
char	**init_env(char **envp);

#endif
