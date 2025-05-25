/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:58:38 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/29 14:52:59 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

int						g_exit_status;

typedef struct s_idx
{
	int					i;
	int					j;
	int					len;
	int					start;
	int					state;
	int					in_s;
	int					in_d;
}						t_idx;

typedef struct ft_cd
{
	char				*path;
	char				*ptr;
	char				**env;
}						t_cd;
typedef struct s_expand_her
{
	int					i;
	int					j;
	int					len;
	char				*final;
	char				*s;
}						t_expand_her;

typedef struct path_cmd
{
	char				*path;
	char				**list;
	char				*tmp;
}						t_path_cmd;

typedef enum e_token
{
	nothing = 0,
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}						t_token;

typedef struct s_redirect
{
	t_token				type;
	int					is_amb;
	char				*store;
	struct s_redirect	*next;
}						t_redirect;

typedef enum e_state
{
	D,
	S,
	G,
	NUL,
}						t_state;
typedef struct s_splitor
{
	char				*in;
	int					len;
	enum e_token		type;
	int					is_amb;
	int					is_exp;
	enum e_state		state;
	struct s_splitor	*next;
	struct s_splitor	*prev;
}						t_splitor;

typedef struct s_envarment
{
	char				*var;
	char				*data;
	struct s_envarment	*next;
}						t_environment;

typedef struct s_here_doc
{
	char				*store;
	int					fd;
	char				*heredoc_file;
	int					idx;
	int					expad;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_command
{
	char				*content;
	char				**arg;
	t_redirect			*doc;
	t_here_doc			*her;
	char				**ar_env;
	int					is_amb;
	int					is_exp;
	int					is_pipe;
	int					len;
	struct s_command	*next;
}						t_command;

typedef struct s_array_env
{
	char				**env_v;
	int					len;
	char				*var_1;
	char				*var_2;
	char				*res;
}						t_envar;

typedef struct s_pre
{
	char				*final;
	int					i;
	int					j;
	int					is_expand;
	int					is_amb;
	t_command			*tmp_cmd;
	t_splitor			*tmp_x;
}						t_pre;

typedef struct s_pipe
{
	int					num_cmd;
	int					**pipefd;
	t_command			*tmp_cmd;
	int					*pids;
	int					heredoc_fd;
	int					i;
	char				*ptr;
	char				**arry;
}						t_pipe;

typedef struct s_ps
{
	int					len_of_arg;
	int					len_of_join;
	char				**new_arg;
	int					idx;
	int					j;
}						t_ps;

typedef struct delet_file
{
	t_command			*tmp;
	t_here_doc			*her;
	char				*ptr;
	char				*file;
	char				*itoa;
}						t_delet;

typedef struct check_var
{
	char				*ptr_1;
	char				*ptr_2;
	t_environment		*elem;
	char				**list;
}						t_check_var;

typedef struct s_dir
{
	char				*final;
	char				**str;
}						t_dir;
typedef struct had_var
{
	int					len;
	int					j;
	char				*s;
	char				*sub;

}						t_had_var;

#endif