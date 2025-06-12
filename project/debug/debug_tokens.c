# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
/*	readline	*/
# include <readline/readline.h>
/* HISTORY*/
# include <readline/history.h>
/*	opendir	*/
# include <dirent.h>

/* errno : cd  */
# include <errno.h>
# include <string.h>

# include <string.h> // bsbah chi errno f cd builtins 

/*  	HEADERS			*/

# include "enums.h"
# include "structs.h"
# include "prototypes.h"
# include "macros.h"
# include "../src/lib/libft.h"

#include <string.h>
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"




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


void	ft_readline(t_minibash	*bash, t_token *tokens, t_cmd *cmd, t_env **env)
{
	(void) env;
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
		//execute_command_pipeline(bash, env, tokens, &cmd);
		tokens = NULL;
		cmd = NULL;
		free (line);
	}
}
