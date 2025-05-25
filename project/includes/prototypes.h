/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:24:29 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/25 15:09:45 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "minishell.h"

/* Built-in */
t_status		echo(t_cmd *cmd);
t_status		cd(t_cmd *cmd, t_minibash *bash);
void			pwd(t_minibash *bash);
void			env(t_minibash *bash);
void			builtin_exit(t_minibash *bash, t_cmd *cmd);
void			unset(t_minibash *bash, char **args);
void			export(t_minibash *bash, t_cmd *cmd);

bool			is_builtins(t_cmd *cmd);



/* Environment */
void			initialize_environment(t_minibash *info, char **env);
void			add_node_to_env(t_env **head, t_env *node);
char			*get_environment(const char *name, t_minibash *bash);
char			*extract_env_name(const char *str);
char			*extract_env_value(const char *str);
t_env			*create_env_node(char *data);
t_env			*create_empty_env_node(char *name);
void			remove_env_variable(t_env **env, char *var);

void			free_env(char **env);

/* Error && Exit*/
void			exit_with_error(const char *msg, int exit, t_minibash *bash);
void			export_error(t_minibash *bash, char *content);
void			print_cmd_err(t_minibash *bash, char *cmd, char *msg, int exit);
void			execute_builtin(t_minibash *bash, t_cmd *cmd);
void			display_errno_exit(char *msg, int status);

/*		EXPORT UTILS	*/
void			display_exported_variable(t_minibash *bash);


/*		PATH 		*/
char			*command_path(t_minibash *bash, t_cmd *cmd);
bool			contains_path_separator(char *command);
bool			is_directory(char *path);
bool			is_file_executable(char *file_path);

/*		EXECUTION  		*/
int 			is_fork_succes(t_minibash *bash, int pid);
void 			execute_pipe_chain(t_minibash *bash, t_cmd *cmd);
bool			has_pipes(t_cmd *cmd);
int				count_pipes(t_cmd *cmd);
char			**env_to_array(t_env *env);
void			free_2d(char **array);


/*		Lexer	*/
int				ft_isspace(int c);
int				ft_isprint(int c); // move into lib
int				is_metachar(char c);
void			ft_lstadd_back_token(t_token **lst, t_token *new_node);
t_token 		*ft_lstnew_token(char *value, int len, t_token_type type, t_state state);
int				lexer(char *input, t_token **tokens);
#endif
