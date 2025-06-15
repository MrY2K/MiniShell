/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/14 17:45:52 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ll(void) { system("leaks -q minishell"); }

void	execute_command_pipeline(t_minibash *bash, t_env **env, t_token *token, t_cmd **cmd)
{
	(void)bash;
	if (token)
	{
		// debug_print_token_list(token); //? DEBUG
		parse_input_commands(&token, cmd, *env);
		// debug_print_cmd_list(*cmd);    //? DEBUG
		execution(bash, env, *cmd);
		free_cmd_list(cmd);
	}
	free_lexer(&token);
}

void	ft_readline(t_minibash	*bash, t_token *tokens, t_cmd *cmd, t_env **env)
{
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr("exit\n");
			exit (bash->exit_status);
		}
		if (lexer(line, &tokens))
		{
			ft_putendl_fd("minishell: syntax error", 2);
			bash->exit_status = 258;
			free_lexer(&tokens);
		}
		execute_command_pipeline(bash, env, tokens, &cmd);
		tokens = NULL;
		cmd = NULL;
		free (line);
	}
}

static void	init_minibash(t_minibash **bash)
{
	*bash = (t_minibash *)malloc(sizeof(t_minibash));
	if (!*bash)
	{
		ft_putstr_fd("minishell: fatal error: cannot allocate memory\n", 2);
		exit(1);
	}
	ft_memset(*bash, 0, sizeof(t_minibash));
	(*bash)->exit_status = 0;
	(*bash)->env = NULL;
}

void	free_minibash(t_minibash **bash)
{
	t_env	*current;
	t_env	*next;

	if (!bash || !*bash)
		return ;
	current = (*bash)->env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free(*bash);
	*bash = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_minibash	*bash;
	t_token		*tokens;
	t_cmd		*cmd;
	int			exit_st;

	(void)ac;
	(void)av;
	tokens = NULL;
	cmd = NULL;
	init_minibash(&bash);
	initialize_environment(bash, env);
	using_history();
	ft_readline(bash, tokens, cmd, &bash->env);
	exit_st = bash->exit_status;
	free_minibash(&bash);
	return (exit_st);
}
