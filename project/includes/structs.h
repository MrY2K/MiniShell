/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:25:15 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/12 23:58:13 by achoukri         ###   ########.fr       */
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
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;




typedef struct s_redirect
{
	t_token_type		type;
	char				*file_path; // store file name
	int					is_ambig;
	struct s_redirect	*next;
}	t_redirect;


/*  export  */

typedef struct s_export_parser // check_var
{
	char	*name; // ptr_1
	char	*value; // ptr_2
	t_env	*env_node; // elem
	char	**list;
}	t_export_parser;

/*		Parsing	*/

typedef struct s_expand_heredoc
{
    char	*str;       // s
    int		index;   // Current index in the input string.   i
	int		j;
    char	*expanded_line;  // Final expanded string.
    int		len;   // Length of the current variable or substring.
}	t_expand_heredoc;

typedef struct s_env_var
{
	char	*str; // s
	char	*sub;
	int		j;
	int		len;
}	t_env_var;

typedef struct	s_heredoc
{
	char			*delimiter; // store
	char			*her_file; // heredoc_file
	int				fd;
	int				index; // idx  //Unique index for this heredoc
	int 			expand; // expad // Flag for whether to expand variables ($VAR) in the heredoc
	struct s_heredoc *next;
}	t_heredoc;


typedef struct s_heredoc_cleanup  // delet_file
{
    t_cmd		*current_cmd; // tmp
    t_heredoc	*current_heredoc; // her
    char         *index_str; // ptr
    char         *temp_path; // file
    char         *full_filepath; // itoa
} t_heredoc_cleanup;

typedef struct s_token  // t_splitor
{
    char            *value; // in 
	int				len;
    t_token_type    type;
	enum e_state	state;
    struct s_token  *next;
} t_token;

typedef struct s_lexer_state 
{
    int				i;
    int				start;
	int				len;
	int				double_q;
	int				single_q;
	t_state		state;
	
} t_lexer_state;

/*		builtins		*/

typedef struct	s_cd
{
	char	**arr_env;
	char	*user_arg;
	char	*path;
}			t_cd;


typedef struct s_env_converter 
{
    char    **env_array;  // Final environment array
    int     len;          // Length of environment list
    char    *tmp_name;    // Temporary storage for name
    char    *tmp_value;   // Temporary storage for value
    char    *tmp_block;    // Temporary storage for "name="
} 		t_env_converter;

/* Execution */
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;



typedef struct s_cmd
{
	char			*main_cmd; // content
	char			**argument; // arg
	char			**env_arr;
	int				has_ambiguous; // is_amb
	int				pipe; // is_pipe
	int				needs_expansion; // is_exp
	int				arg_len; // len 
	t_heredoc		*heredoc; // her
	t_redirect		*redirections; // doc
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	int     			cmd_count; // num_cmd
	int					**pipe_fds; // pipefd
	int					fd_heredoc;
	t_cmd				*current_cmd; // tmp_cmd
	int					*child_pids; // pids
	char				*path; // ptr
	char				**arr_env;
 
}	t_pipe;


typedef struct s_minibash
{
	t_env	*env;
	int		exit_status;
}	t_minibash;


#endif
