/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:21:23 by lderidde          #+#    #+#             */
/*   Updated: 2025/01/27 15:02:20 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

typedef struct s_ast_n	t_ast_n;

int		execute_command(t_ast_n *node);

//EXEC_REDIR
int		handle_file(t_ast_n *node, int check, int i);
int		handle_redir(t_ast_n *node);
void	reset_redir(t_ast_n *node);
int		err_fork_pline(int *pipes);
void	dup_redir(t_ast_n *node, int i);

//EXEC_BUILTIN
int		is_builtin(char *str);
int		exec_builtin(t_ast_n *node);

//EXEC_PLINE
void	exec_pcmd(t_ast_n *pcmd);
void	exec_pchild(int *pipes, int index, t_ast_n *pcmd, int cmds);
int		end_pline(pid_t last_pid, t_ast_n **pline);
int		exec_pline(t_ast_n **pline);

//EXEC_SUBSH
int		exec_shcmd(t_ast_n *node);
int		execute_shcommand(t_ast_n *node);
int		exec_subsh(t_ast_n *node);

//EXEC_HEREDOC
void	expander_here(char **str, t_ast_n *node);
void	here_remove_quote(t_ast_n *node, int j, char c);
int		ifhere_remove_quote(t_ast_n *node, int j);
void	read_input(t_ast_n *node, int j);
void	here_doc(t_ast_n *node, int i);

//EXEC_UTILS
int		execis_validchar(char c);
int		execget_var_len(char *str, t_ast_n *node, int *j);
int		get_dup_len(char *str, t_ast_n *node);
int		execvalid_next(char c);
char	*execextract_env(char *str, char **envp);

//EXEC_CMD
int		count_cmds(t_ast_n **pline);
char	*find_path(char *cmd, char **env);
void	return_error(char *arg, char *msg, int code, t_ast_n *node);
int		exec(t_ast_n *node);
int		exec_scmd(t_ast_n *node);

#endif
