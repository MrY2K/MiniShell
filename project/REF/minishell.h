/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/10/07 13:06:08 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

// call all the libriries we need in the project
# include "./includes/libft/libft.h"
# include "structures.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//////////////////////////////  Parsser  /////////////////////////////////

// ---condition---
int				quotes(t_splitor *start);
int				redirection(t_splitor *start);
int				ft_condition(t_splitor *start);
// ---function to skip---
void			ft_skip_spaces(t_splitor **tmp_x);
void			ft_skip_spaces_in_count(t_splitor **tmp_x);
void			ft_skip_not_word(t_splitor **tmp_x, t_environment *my_env);
void			ft_skip_spaces_in_count__2(t_splitor **tmp_x);
// ---function to join---
char			**ft_double_and_sigle(t_splitor **tmp_x, t_environment *my_env,
					int j, char ***arr_join);
void			ft_join_double(char ***join, t_splitor **tmp_x,
					t_environment *my_env, int j);
char			**ft_word(t_splitor **tmp_x, t_environment *my_env, int j,
					char ***arr_arg);
void			ft_join_words(char ***join, t_splitor **tmp_x,
					t_environment *my_env, int j);
void			ft_join_word_2(char ***join, t_splitor **tmp_x,
					t_environment *my_env, int j);
void			ft_command(t_splitor **x, t_command **cmd,
					t_environment *my_env);
void			ft_free_lexer(t_splitor **x);

int				ft_lexer(char *str_input, t_splitor **x);
void			ft_get_word(char *s, t_idx *var, t_splitor **x);
void			ft_get_char(char *s, t_idx *var, t_splitor **x);
void			ft_check_env(char *s, t_idx *var);
void			ft_get_env(char *s, t_idx *var, t_splitor **x);
void			ft_her_dir(t_splitor **x, t_idx *var, char *s);
t_environment	*ft_stock_envarment(char **env);
void			print_t_command(t_splitor *cmd);
void			print_redirect_list(t_redirect *head);
// ---------
void			ft_free_env(t_environment **x);
void			ft_free_lexer(t_splitor **x);
void			ft_free_command(t_command **lst);
// ---------
int				ft_search(char *s, char *d);
int				ft_isspace(char c);
t_token			ft_get_token(char str_input);
int				ft_check_input(char str_input);
t_state			ft_get_state(t_idx *var, char str_input);
int				ft_condition(t_splitor *start);
int				redirection(t_splitor *start);
int				quotes(t_splitor *start);
int				ft_handler_syn_error(t_splitor **x);
// int			ft_lexer(char *input, t_splitor **x);
// ---------
t_environment	*new_node(void *var, void *data);
void			add_back_node(t_environment **lst, t_environment *new);
t_environment	*ft_stock_envarment(char **env);
char			*ft_expand(char *arg, t_environment **my_env);
// ---------
void			ft_count_parameters(t_splitor *tmp_x, int *count);
void			ft_command(t_splitor **x, t_command **cmd, t_environment *env);
void			ft_add_command(t_command **lst, t_command *new);
t_command		*ft_new_command(t_splitor **tmp_x, t_environment *env);
t_command		*ft_last_command(t_command *lst);
void			ft_free_argment(char **arg);
char			**ft_join_arg(char **arg, char **join);
// ---------
void			ft_not_pipe(t_command **new_node, t_splitor **tmp_x,
					t_environment *my_env);

void			ft_skip_spaces(t_splitor **tmp_x);
void			ft_skip_spaces_in_count(t_splitor **tmp_x);

void			ft_skip_general(t_splitor **tmp_x, int *i, t_command **new_node,
					t_environment *my_env);

// ---------
void			ft_fill_red(t_command **cmd, t_splitor **x,
					t_environment *my_env);
t_redirect		*ft_new_redir(void *content, t_token type, int is_amb);
void			ft_add_redir(t_redirect **lst, t_redirect *new);
char			*ft_skip_direction(t_splitor **tmp_x, t_environment *my_env,
					int *is_amb, int her);
t_redirect		*ft_last_redir(t_redirect *lst);

void			ft_join_arr(char ***arr_join, char *in);
int				ft_len_arg(char **arg);
char			**ft_split_expand(char ***join, char *s);

//////////////////////  Execution  ////////////////////////

void			ft_exute(t_environment **var, t_command *list);
void			ft_free_leaks(t_command *list);
void			parent_proc(int pid);
void			hundle_redirections(t_command *list);
void			run_command(t_command *list, t_environment **var);
int				is_directory(char *path);
void			ft_access_2(char *ptr, char **str, char **env_v);
void			ft_access_1(char *ptr, char **str, char **env_v);
void			ft_access(char *ptr, char **str, char **env_v);
int				built_in_exist(t_command *list);
void			built_in(t_environment **var, t_command *list);
void			execution_cmd(t_environment **var, t_command *list, char **new);
int				run_herdoc_built(t_environment **var, t_command *cmd);

int				ft_strcmp(char *s1, char *s2);
char			**create_argv(t_splitor *elem);
char			*path_command(char *ptr, char **env);
t_environment	*ft_stock_envarment(char **env);
int				test_exist(t_environment **var, char **list);
void			run_simple_cmd(t_command *list, t_environment **var);
void			free_args(char **args);
char			**split_line(char *ptr);
char			**split_var(char *ptr);

void			hundle_command(t_command *list, char **env);
void			handle_pipe(t_command *list, t_environment **var);

///////////////////////// Redirections  //////////////////////////
void			hundle_redir_out(char *file, int amb);
void			hundle_redir_in(char *file, int amb);
void			hundle_dredir_out(char *file, int amb);

/////////////////////////  her doc  //////////////////////////

bool			handle_here_doc(t_environment **var, t_command *cmd);
void			create_files(t_command *cmd, char *itoa);
int				ft_cmp_delimeter(t_command *tmp_cmd, t_environment **var);
int				handle_fork(t_here_doc *tmp_her, t_environment **var);
void			hundle_chil_pro(t_here_doc *tmp_her, t_environment **var);
void			write_in_file(t_here_doc *tmp, char *line, t_environment **var);
char			*ft_expand_in_her(char *line, t_environment *my_env);
char			*ft_handle_var(char *line, int *i, t_environment *my_env,
					char **final);
void			delet_files(t_command *cmd);
void			sig_herdoc(int sig);
int				count_herdoc(t_command *tmp);
int				herdoc_exist(t_command *list);
char			*ft_name_file(t_here_doc *tmp);
t_here_doc		*new_node_her(char *file, int fd, int x, int is_expand);
void			add_back_node_her(t_here_doc **her, t_here_doc *new_her);

/////////////////////////  function redirections  //////////////////////////
char			**get_len(char **args, t_redirect *redir);
char			*git_type_redir(t_redirect *redir);
char			**ft_new_args(char **args, t_redirect *redir);
int				test_redir(t_command *list);

/////////////////////////  execut_cmd  //////////////////////////
void			ft_run_pipes(t_pipe *hd_p, int i, t_environment **var);
int				pipe_exist(t_command *list);
int				num_pipe(t_command *list);
char			*command_execut(t_command *list);
int				**return_pipe(int num_cmd);
t_command		*get_list_command(t_command *list);
void			close_free_wait(int *pids, int **pipefd, int num_cmd);

/////////////////////////  signal  //////////////////////////

int				hundle_file_herdoc(t_command *list);
void			handl_sig_exec(int sig);
void			handle_sig(int sig);
void			hhandle_sig(int sig);
int				chech_fork(int pid);

// ///////            Commands         //////////////////////////////////

void			ft_cd(t_environment **var, t_command *list);
void			complete_cd(char *path, char *ptr, char **env);
void			complete_cd_1(t_environment **var, char *path, char **env);
void			ft_setenv_list(t_environment **var, char *old, char **env,
					char *path);
t_environment	*find_env(t_environment *my_var, char *old);
void			printf_error_cd(char *s, int exit);

void			ft_unset(t_environment **var, t_command *list);
t_environment	*delet_first_node(t_environment **my_env);
void			ft_error(char *str, char *ptr);
void			delet_first(t_environment **var, char *ptr);
void			delet_environment(t_environment **var, char *str);

void			ft_pwd(t_command *list);
void			ft_env(t_environment **var);
void			ft_echo(t_command *list);
void			ft_exit(t_environment **var, t_command *list);

void			ft_export(t_environment **var, t_command *str);
int				ft_str_eqal(char *ptr, char c);
char			**split_line(char *ptr);
int				check_is_valid_1(char *str);
void			export_1(t_environment **var, t_command *str, int *i);
int				ft_isalnum_exp(int c);
void			print_export(t_environment **var);
void			check_dolar_is(char *str, t_environment *var, t_command *s);
int				exist_redir(char *ptr);
void			affiche_export(char **str, t_environment **var);
int				ft_is_num(char *str);
void			free_args(char **args);
void			free_args_1(char **args);
char			*first_word(char *ptr);

char			**array_env(t_environment **var);
char			*ft_strjoin_1(char *s1, char *s2);
int				len_var(t_environment *var);

//////////////////////     free      /////////////////////////////////
void			free_ft_split(char **list);
char			*ft_getenv(char *path, char **env);
void			free_pid_pipe(int *pids, int **pipefd, int num_cmd);
char			*ft_join(char *s1, char *s2);
int				ft_check_built(t_command *list);
void			print_error_amb(int ext);
void			print_error_exit(char *ptr, int ext);
#endif
