/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/29 17:58:28 by achoukri         ###   ########.fr       */
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




// ******  Readline

void	free_lexer(t_token **token)
{
	t_token	*cur;

	while (*token)
	{
		cur = *token;
		*token = (*token)->next;
		if (cur->value)
		{
			free(cur->value);
			cur->value = NULL;
		}
		free(cur);
		cur = NULL;
	}
}

void	ft_readline(t_minibash	*bash, t_token *tokens, t_cmd *cmd, t_env *env)
{
	(void)env;
	(void)cmd;
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
		tokens = NULL;
		free (line);
	}

}



int main(void)
{
	t_minibash	*bash = NULL;
	t_token		*tokens = NULL;
	t_cmd		*cmd = NULL;
	t_env		*env = NULL;

	signals();
	ft_readline( bash, tokens, cmd, env);

	return (0);
}
