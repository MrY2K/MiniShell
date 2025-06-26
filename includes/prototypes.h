/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:24:29 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/25 12:31:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "../src/lib/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "enums.h"

/* Signals */
void			sigint_handler(int signum);
void			handle_sigquit(int sign_al);
void			here_pipe_signals(int sig_nal);

/* Built-in */
void			builtin_cd(t_minibash	*bash, t_env **env, t_cmd	*cmd);
void			builtin_echo(t_minibash *bash, t_cmd *cmd);
void			builtin_env(t_minibash *bash, t_env	**env);
void			builtin_exit(t_minibash *bash, t_cmd *cmd);
void			builtin_pwd(t_minibash *bash, t_cmd *cmd);
void			builtin_unset(t_minibash *bash, char **args, t_env **env);

bool			is_builtins(t_cmd *cmd);
void			execute_builtins(t_minibash *bash, t_env **env, t_cmd *cmd);
bool			is_parent_builtins(t_cmd *cmd);
void			execute_parent_builtin(t_minibash *bash, t_env **env,
					t_cmd *cmd);

/*		Export   */
void			builtin_export(t_minibash *bash, t_env **env, t_cmd *cmd);
bool			is_allowed_variable_character(char c);
bool			is_contains_char(char	*str, char target_char);
t_env			*create_new_node(void *var, void *data);
char			**split_var_value_pair(char	*str);
void			process_export_args(t_env **env, t_cmd *cmd, int *index);
void			export(char **args, t_env *env);

/* Error && Exit*/
void			exit_with_error(const char *msg, int exit, t_minibash *bash);
void			export_error(t_minibash *bash, char *content);
void			print_cmd_err(t_minibash *bash, char *cmd, char *msg, int exit);
void			display_errno_exit(char *msg, int status);
void			display_syntax_error(t_minibash *bash);
void			execute_error(t_minibash *bash, char *msg);
void			display_ambiguous_errno(t_minibash *bash, int exit_st);
void			cd_error(t_minibash *bash);
void			redirection_error(t_minibash *bash);

int				is_valid_exit_arg(char *arg);
long long		ft_atoll(const char *str);

/*		PATH				*/
char			*path_command(char *cmd, char **env, t_minibash *minibash);
char			*get_env_variable(char *name, char **env);

/*		accses*/

int				ft_is_directory(char *path);
void			ft_handle_error_exit(t_minibash *bash,
					char **args, char *msg, int code);
void			acc_ess(t_minibash *bash, char **env, char *path, char **args);
void			ft_handle_file_not_found(t_minibash *bash, char **env,
					char *path, char **args);
void			ft_handle_permission_denied(t_minibash *bash,
					char *path, char **args);

/*		Lexer	*/
int				ft_isspace(int c);
int				ft_isprint(int c);
int				is_metachar(char c);
void			ft_lstadd_back_token(t_token **lst, t_token *new_node);
t_token			*ft_lstnew_token(char *value, int len,
					t_token_type type, t_state state);
int				lexer(char *input, t_token **tokens);
t_state			get_state(char c, t_lexer_state *ls);
void			handle_metachar(char *input, t_lexer_state *ls,
					t_token **tokens);
void			handell_append_herdoc(t_token **tokens, char *input,
					t_lexer_state *ls);
void			env_variables(char *input, t_lexer_state *ls);
void			shell_variable(char *input, t_lexer_state *ls);
void			handle_env_variables(char *input, t_lexer_state *ls,
					t_token **tokens);
t_token_type	get_token_type(char c);
void			skip_spaces(t_token	**cur_node);

/*  lexer handell syntx error   */

int				has_syntax_error_at_start(t_token **start);
int				check_middle_syntax(t_token **middle, enum e_state NOR);

/*   ENV 		*/

char			**convert_env_list_to_array(t_env **env);
char			*get_environment_variable(char	**env, char *path);
void			update_env_var(t_env **env, char **arr_env,
					char *path, char *old);
void			free_env_arr(char **arr_env);
char			*create_env_entry(t_env_converter *conv, t_env *node);
int				get_environment_len(t_env	*env);
void			initialize_environment(t_minibash *info, char **env);
void			add_node_to_env(t_env **head, t_env *node);
void			remove_env_variable(t_env **env, char *var);

/*  Free  */

void			free_lexer(t_token **token);
void			free_minibash(t_minibash **bash);

/*		EXECUTION 				*/
int				is_fork_succes(t_minibash *bash, int pid);
bool			has_pipes(t_cmd *cmd);
int				count_pipes(t_cmd *cmd);
char			**convert_env_list_to_array(t_env **env);
void			free_2d(char **array);
void			execution(t_minibash *bash, t_env **env, t_cmd *cmd);
bool			has_herdoc(t_cmd *cmd);
bool			is_builtins(t_cmd *cmd);
bool			has_redirections(t_cmd *cmd);
char			*ft_strjoin_with_null(char *s1, char *s2);
void			execute_command(t_minibash *bash, t_env **env, t_cmd *cmd);
void			handle_pipes(t_minibash *bash, t_env **env, t_cmd *cmd);
int				count_pipes(t_cmd *cmd);
int				**allocate_pipe_fds(t_minibash *bash, int command_count);
void			cleanup_pipe_resources(t_pipe *pi_pe);

/*   REDIRECTIONS     */

void			handle_redirections(t_minibash *bash, t_cmd *cmd);
int				validate_redirection_file(t_cmd *list);

/*		herdoc		*/

int				handle_heredoc_input(t_cmd *cmd);
int				setup_heredoc_input(int fd);
char			*generate_heredoc_file_name(t_heredoc *her);
t_cmd			*get_last_heredoc(t_cmd *cmd);
int				open_heredoc_file(char *file);
char			*expand_env_var_her(t_expand_info *info);

/*   parsing  */

void			parse_command(t_token **token, t_cmd **cmd, t_env *env);
bool			handle_heredocs(t_minibash *bash, t_env **env, t_cmd *tmp_cmd);
void			create_tmp_herdoc_files(t_cmd *tmp_cmd, char *idx_to_char);
int				process_her_with_signals(t_minibash *bash,
					t_env **env, t_cmd *cmd);
char			*get_path(t_heredoc *heredoc);
void			write_in_heredoc_files(t_minibash *bash, t_env **env,
					t_heredoc *heredoc, char *line);
char			*expand(t_minibash *bash, t_env **env, char *str);
void			lookup_env_var(t_env **env, char *arg, char **str, int *i);
int				search(const char *str, const char *to_find);
void			parse_input_commands(t_token **token_list, t_cmd **cmd_list,
					t_minibash *b);
void			append_command(t_cmd **cmd_list, t_cmd *new_cmd);
t_cmd			*last_command(t_cmd *cmd_list);
t_cmd			*create_new_command(t_token **tok_ptr, t_minibash *b);
void			join_to_arg_array(char ***arg_arr, char *tok_str);
void			process_non_pipe_segment(t_cmd **cmd_node,
					t_token **tok_ptr, t_minibash *b);
void			handle_token_part(t_cmd **cmd_node, t_token **tok_ptr,
					t_minibash *b, char ***arg_arr);
void			join_to_arg_array(char ***arg_arr, char *tok_str);
void			process_redirections(t_cmd **cmd, t_token **tokens,
					t_minibash *b);
int				get_arg_count(char **args);
void			skip_nonword_tokens(t_token **tok_ptr,
					t_minibash *b);
void			skip_whitespace(t_token **tok_ptr);
char			**combine_arguments(char **args, char **addition);
void			free_argument_array(char **arr);
char			**process_word(t_token **tok_ptr, t_minibash *env, int flag,
					char ***arg_arr);
int				is_redirection(t_token *node);
char			**process_quoted(t_token **tok_ptr, t_minibash *b, int flag,
					char ***arg_arr);

/*   parse utils: */

int				redirection(t_token *start);
int				ft_len_arg(char **arg);
int				ft_search(char *s, char *d);
int				is_quote(t_token *head);

char			**ft_join_arg(char **arg, char **join);
void			ft_join_arr(char ***arr_join, char *in);

void			ft_join_double_2(char ***arr_join, t_token **tmp_t,
					t_minibash *env, int j);
void			ft_join_word_2(char ***arr_join, t_token **tmp_t,
					t_minibash *env, int j);
void			ft_join_words(char ***arr_join, t_token **tmp_t,
					t_minibash *env, int j);

//more joiner for process quotes
void			ft_join_next(char ***arr_join, t_token **tmp_x, t_minibash *b,
					int j);
void			ft_join_double(char ***arr_join, t_token **tmp_t,
					t_minibash *b, int j);

char			*ft_expand(char *arg, t_minibash *b);
char			**ft_split_expand(char ***arr_join, char *s);
void			ft_go_to_env(char **s, char *arg, int *i, t_minibash **b);

//  RED2
char			*ft_fill_final(char **s);
int				ft_check_ambiguous(t_token *tmp_t, t_minibash *b);
int				ft_check_quote(t_token **tmp_t, char **final);
char			*ft_skip_direction(t_token **tmp_t, t_minibash *b,
					int *is_ambig, int her);

/* free parsing   */

void			free_cmd_list(t_cmd **cmd_list);
void			ft_skip_spaces(t_token **tpm_t);
void			ft_add_red(t_redirect **lst, t_redirect *_new);
t_redirect		*ft_last_redir(t_redirect *lst);
t_redirect		*ft_new_redir(void *content, t_token_type type, int is_ambig);
void			ft_next(t_token **tok_ptr, t_cmd **cmd_ptr);
void			add_back_node_her(t_heredoc **her, t_heredoc *new_her);
t_heredoc		*new_node_her(char *file, int fd, int tokens, int is_expand);
void			ft_handle_red(t_expand_heredoc *id, char *final, t_minibash *b);

#endif
