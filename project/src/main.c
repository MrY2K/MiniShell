/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/06 18:54:36 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <string.h>
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"

void	ll(void) { system("leaks -q minishell"); }

const char *token_type_to_str(t_token_type type)
{
	switch (type)
	{
		case TOKEN_WORD: return "WORD";
		case TOKEN_SPACE: return "SPACE";
		case TOKEN_PIPE: return "PIPE";
		case TOKEN_ENV: return "ENV";
		case TOKEN_REDIR_IN: return "REDIR_IN";
		case TOKEN_REDIR_OUT: return "REDIR_OUT";
		case TOKEN_REDIR_APPEND: return "APPEND";
		case TOKEN_HEREDOC: return "HEREDOC";
		case TOKEN_NEWLINE: return "NEWLINE";
		case TOKEN_EOF: return "EOF";
		case TOKEN_WHITE_SPACE: return "WHITESPACE";
		case TOKEN_SINGLE_QUOTE: return "SINGLE_QUOTE";
		case TOKEN_DOUBLE_QUOTE: return "DOUBLE_QUOTE";
		default: return "UNKNOWN";
	}
}

const char *state_to_str(t_state state)
{
	switch (state)
	{
		case Normal: return "NORMAL";
		case Single: return "SINGLE";
		case Double: return "DOUBLE";
		case NUL: return "NULL";
		default: return "UNKNOWN";
	}
}

void	print_tokens(t_token *tokens)
{
	int i = 0;
	printf(CYAN "\n--- Token Debug ---\n" RESET);
	while (tokens)
	{
		if (tokens->value)
		{
			printf(CYAN "[%02d] Token: %-20s | Len: %-2d | Type: %-14s | State: %-10s\n" RESET,
				i++,
				tokens->value,
				tokens->len,
				token_type_to_str(tokens->type),
				state_to_str(tokens->state));
		}
		else
		{
			printf(CYAN "[%02d] Token: %-20s | Len: %-2d | Type: %-14s | State: %-10s\n" RESET,
				i++,
				"(null)",
				tokens->len,
				token_type_to_str(tokens->type),
				state_to_str(tokens->state));
		}
		tokens = tokens->next;
	}
	printf(CYAN "--- End Debug ---\n\n" RESET);
}




// ****** ✅     ✅   ✅     ✅   ✅   Readline    ✅     ✅   ✅     ✅   ✅     ✅


void	execute_command_pipeline(t_minibash *bash, t_env **env, t_token *token, t_cmd **cmd)
{
	if (!token && !env)
	{
		parse_command(&token, cmd, *env);
		execution(bash, env, *cmd);
	}
	//free_command_resources(cmd);
	free_lexer(&token);
}


void	ft_readline(t_minibash	*bash, t_token *tokens, t_cmd *cmd, t_env **env)
{
	(void) env;
	(void) cmd;
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr("exit");
			exit (bash->exit_status);
		}
		if (lexer(line, &tokens))
		{
			ft_putendl_fd("minishell: syntax error", 2);
			//bash->exit_status = 258;
			//free_lexer(&tokens);
		}
		else
			print_tokens(tokens); // debug
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

int	main(int ac, char **av, char **env)
{
	t_minibash	*bash;
	t_token		*tokens;
	t_cmd		*cmd;

	(void)ac;
	(void)av;
	tokens = NULL;
	cmd = NULL;
	init_minibash(&bash);
	initialize_environment(bash, env);
	if (!bash->env)
	{
		ft_putstr_fd("minishell: fatal error: environment initialization failed\n", 2);
		free(bash);
		exit(1);
	}
	using_history();
	ft_readline(bash, tokens, cmd, &bash->env);
	free_minibash(&bash); // this is not finishe yet , only free env 
	return (bash->exit_status);
}
