/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lderidde <lderidde@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 08:23:27 by lderidde          #+#    #+#             */
/*   Updated: 2025/02/05 13:45:47 by lderidde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include <unistd.h>

typedef struct s_node	t_node;
typedef struct s_msh	t_msh;

typedef enum e_state
{
	UNDEF,
	_AND,
	_OR,
	_CMD,
	_PLINE,
	_SUBSH
}		t_state;

typedef enum e_redir
{
	_NR,
	_RED_L,
	_RED_R,
	_RED_DR,
	_RED_DL
}		t_redir;

typedef struct s_ast_n
{
	t_state			state;
	struct s_ast_n	*parent;
	struct s_ast_n	*left;
	struct s_ast_n	*right;
	struct s_ast_n	**pline;
	t_msh			*msh;
	char			*cmd;
	char			**args;
	int				fds[2];
	int				_stdout;
	int				_stdin;
	int				save_stdo;
	int				save_stdi;
	t_redir			*redir;
	char			*input;
	char			**files;
	bool			sh;
}					t_ast_n;

typedef struct s_nodell
{
	t_node			*node;
	struct s_nodell	*next;
}					t_nodell;

t_ast_n		*get_ast(t_msh *msh, t_node *lst);
t_nodell	*cutll(t_node *lst, t_node *expected, size_t limiter);
t_node		*get_top_token(t_node *lst, t_state *state);

// recurce
t_ast_n		*create_ast_n(t_node *lst, t_ast_n *parent, t_msh *msh, bool subsh);
// redir
t_redir		get_redir(t_node *node);
void		create_redir(t_node *cpy, t_ast_n *self);
void		create_redir_subsh(t_node *head, t_ast_n *self);
// cmd
void		create_cmd(t_ast_n *self, t_node *lst);
// subsh
void		create_subsh(t_ast_n *parent, t_node *lst, t_msh *msh);
// pipeline
void		create_pline(t_ast_n *self, t_node *lst, t_node *token, t_msh *msh);
// and_or
void		create_and_or(t_ast_n *parrent, t_node *lst, t_node *token,
				t_msh *msh);

// free
void		free_ast(t_ast_n *node);
void		free_lltab(t_nodell *nodell);

#endif
