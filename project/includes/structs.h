/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:25:15 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/20 22:29:21 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

// structure for combining arguments.
typedef struct s_ps
{
	int		idx;
	int		j;
	int		arg_len;
	int		join_len;
	char	**new_args;
}				t_ps;

// redirection struct 
typedef struct s_cmd	t_cmd;
typedef struct s_env	t_env;

typedef struct s_redirect
{
	t_token_type		type;
	char				*file_path;
	int					is_ambig;
	struct s_redirect	*next;
}	t_redirect;

/*  export  */
typedef struct s_export_parser // check_var
{
	char	*name;
	char	*value;
	t_env	*env_node;
	char	**list;
}	t_export_parser;

/*		Parsing	*/

typedef struct s_env_var
{
	char	*str;
	char	*sub;
	int		j;
	int		len;
}	t_env_var;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*her_file;
	int					fd;
	int					index;
	int					expand;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_heredoc_cleanup
{
	t_cmd		*current_cmd;
	t_heredoc	*current_heredoc;
	char		*index_str;
	char		*temp_path;
	char		*full_filepath;
}	t_heredoc_cleanup;

typedef struct s_token
{
	char			*value;
	int				len;
	t_token_type	type;
	enum e_state	state;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer_state 
{
	int				i;
	int				start;
	int				len;
	int				double_q;
	int				single_q;
	t_state			state;
}	t_lexer_state;

/*		builtins		*/

typedef struct s_cd
{
	char	**arr_env;
	char	*user_arg;
	char	*path;
}			t_cd;

typedef struct s_env_converter 
{
	char	**env_array;
	int		len;
	char	*tmp_name;
	char	*tmp_value;
	char	*tmp_block;
}			t_env_converter;

/* Execution */
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*main_cmd;
	char			**argument;
	char			**env_arr;
	int				has_ambiguous;
	int				pipe;
	int				needs_expansion;
	int				arg_len;
	t_heredoc		*heredoc;
	t_redirect		*redirections;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	int					cmd_count;
	int					**pipe_fds;
	int					fd_heredoc;
	t_cmd				*current_cmd;
	int					*child_pids;
	char				*path;
	char				**arr_env;
}	t_pipe;

typedef struct s_minibash
{
	t_env	*env;
	int		exit_status;
}	t_minibash;

typedef struct s_expand_heredoc //t_pre
{
	char		*s;
	char		*expanded_line;
	int			len;
	int			index;
	int			j;
	int			i;
	int			is_expand;
	int			is_ambig;
	t_cmd		*tmp_cmd;
	t_token		*tmp_t;
}	t_expand_heredoc;

typedef struct s_dir
{
	char				*final;
	char				**str;
}						t_dir;

#endif
