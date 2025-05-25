/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:24:29 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/25 20:15:26 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

#include "../src/lib/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "structs.h"     
# include "enums.h"     

/* Signals */
// void     sigint_handler(int signum);
void            signals(void);

/* Parsing */
int             ft_isspace(char c);


/* Built-in */
t_status		echo(t_cmd *cmd);
t_status		cd(t_cmd *cmd, t_minibash *info);
void			pwd(t_minibash *bash);
void			env(t_minibash *bash);

/* Environment */
void			initialize_environment(t_minibash *info, char **env);
void			add_node_to_env(t_env **head, t_env *node);
char			*get_environment(const char *name, t_minibash *bash);
char			*extract_env_name(const char *str);
char			*extract_env_value(const char *str);
t_env			*create_env_node(char *data);
t_env			*create_empty_env_node(char *name);

/* Error && Exit*/
void			exit_with_error(const char *msg, int exit, t_minibash *bash);

#endif
