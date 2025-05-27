/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:25:15 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/27 11:19:24 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"


/*		Parsing	*/

typedef struct s_token 
{
    char            *value;
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
	bool			pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipe
{
	int     			cmd_count;
	int					**pipe_fds;
	t_cmd				*current_cmd;
	int					*child_pids;
	char				*path;

}	t_pipe;


typedef struct s_minibash
{	char	**path;
	t_env	*env;
	int		exit_status;
}	t_minibash;


#endif
