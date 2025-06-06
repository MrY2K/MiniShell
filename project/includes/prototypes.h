/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:24:29 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/06 16:58:46 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "minishell.h"

/* Built-in */
void	builtin_cd(t_minibash	*bash, t_env **env, t_cmd	*cmd);
void	builtin_echo(t_minibash *bash, t_cmd *cmd);
void	builtin_env(t_minibash *bash, t_env	**env);
void	builtin_exit(t_minibash *bash, t_cmd *cmd);
void	builtin_pwd(t_minibash *bash, t_cmd *cmd);
void	builtin_unset(t_minibash *bash, char **args);

bool			is_builtins(t_cmd *cmd);
void	execute_builtins(t_minibash *bash, t_env **env, t_cmd *cmd);



/* Environment */
// void			initialize_environment(t_minibash *info, char **env);
// void			add_node_to_env(t_env **head, t_env *node);
// char			*get_environment(const char *name, t_minibash *bash);
// char			*extract_env_name(const char *str);
// char			*extract_env_value(const char *str);
// t_env			*create_env_node(char *data);
// t_env			*create_empty_env_node(char *name);
void			remove_env_variable(t_env **env, char *var);

//void			free_env(char **env);

/**/

/* Error && Exit*/
void			exit_with_error(const char *msg, int exit, t_minibash *bash);
void			export_error(t_minibash *bash, char *content);
void			print_cmd_err(t_minibash *bash, char *cmd, char *msg, int exit);
// void			execute_builtin(t_minibash *bash, t_cmd *cmd);
void			display_errno_exit(char *msg, int status);

/*		EXPORT UTILS	*/
//void			display_exported_variable(t_minibash *bash);


// /*		PATH 		*/
char			*command_path(t_minibash *bash, t_cmd *cmd);
bool			contains_path_separator(char *command);
bool			is_directory(char *path);
bool			is_file_executable(char *file_path);

/*		EXECUTION  		*/
int 			is_fork_succes(t_minibash *bash, int pid);
void 			execute_pipe_chain(t_minibash *bash, t_cmd *cmd);
bool			has_pipes(t_cmd *cmd);
int				count_pipes(t_cmd *cmd);
char 			**convert_env_list_to_array(t_env **env);
void			free_2d(char **array);


/*		Lexer	*/
int				ft_isspace(int c);
int				ft_isprint(int c); // move into lib
int				is_metachar(char c);
void			ft_lstadd_back_token(t_token **lst, t_token *new_node);
t_token 		*ft_lstnew_token(char *value, int len, t_token_type type, t_state state);
int				lexer(char *input, t_token **tokens);

// lexer handell syntx error 

int				has_syntax_error_at_start(t_token **start);
void			skip_spaces(t_token	**cur_node);
int				check_middle_syntax(t_token **middle);


/*    ✅  ✅  ✅   builtins second edition ✅   ✅   ✅ */

	/*   ENV 		*/
	
char 	**convert_env_list_to_array(t_env **env);
char	*get_environment_variable(char	**env, char *path);
void	update_env_var(t_env **env, char **arr_env, char *path, char *old);
void	free_env_arr(char **arr_env);
char 	*create_env_entry(t_env_converter *conv, t_env *node);
int		get_environment_len(t_env	*env);
void	initialize_environment(t_minibash *info, char **env);


// error package 

void	display_ambiguous_errno(t_minibash *bash, int exit_st);

// free 

void	free_lexer(t_token **token);
void	free_minibash(t_minibash **bash);

// ** execution 
void	execution(t_minibash *bash, t_env **env, t_cmd *cmd);
bool	has_herdoc(t_cmd *cmd);
bool	is_builtins(t_cmd *cmd);
bool	has_redirections(t_cmd *cmd);
char	*ft_strjoin_with_null(char *s1, char *s2);

// execute 
void	execute_command(t_minibash *bash, t_env **env, t_cmd *cmd);

// path 


char	*command_path(t_minibash *bash, t_cmd *cmd);

// handelle pipes 

void	handle_pipes(t_minibash *bash, t_env **env, t_cmd *cmd);
int		count_pipes(t_cmd *cmd);

// REDIRECTIONS 

void	handle_redirections(t_minibash *bash, t_cmd *cmd);

// herdoc 

int		handle_heredoc_input(t_cmd *cmd);

// parsing 

void	parse_command(t_token **token, t_cmd **cmd, t_env *env);


#endif
