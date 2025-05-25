/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/25 20:48:05 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

char	**split_tokens(const char *line);
void	ll(void) { system("leaks -q minishell"); }

typedef struct s_redir
{
	
    int            type;      		// e.g. REDIR_IN, REDIR_OUT, APPEND, HERE_DOC
    char          *filename;  		// target file name (from next token)
    struct s_redir *next;    		// next redirection

} t_redir;

typedef struct s_command
{
	
    char       **argv;       		// argv array (command + arguments), NULL-terminated
    t_redir    *redirs;     		// linked list of redirections for this command
    struct s_command *next;  		// next command in pipeline (or NULL)

} t_command;

typedef enum e_token_type
{
	nothing,
	WORD = -1,
	PIPE_LINE = '|',
	HERE_DOC,
	DREDIR_OUT,
	REDIR_OUT = '>',
	REDIR_IN = '<',
	
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	DOUBLE_QUOTE = '\"',
	QOUTE = '\'',
	ENV = '$',

}					t_token_type;

typedef struct	s_token 
{
	
	t_token_type	type;
	char			*value;
	struct s_token *next;

}	t_token;


int main(int ac, char **av, char **env)
{
	char *line;

	signals();
	(void)ac;
	(void)av;
	(void)env;
	env = NULL;
	// env = // GET_ENV(emv)
	while (1)
	{
		line = readline("minishell$ ");
		if (!line) /* Ctrl-D: readline returns NULL */
			return (rl_clear_history(), write(1, "exit\n", 5), 1);
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			// INIT	
			printf("|line: %s\n|", line);		//  echo "Hello $USER" > output.txt
												// [ WORD:echo ] → [ WORD:"Hello $USER" ] → [ REDIR_OUT:> ] → [ WORD:output.txt ]
			
			ft_lexer(line, int **x)
			// parser()
		}

		/* => Lexer => tokenizer => parser */
		
		// call the lexter on line = minishell$ echo "Hello $USER" > output.txt 
		// if (lexer(line, ) == BAD)
		// {
		// 	// Print Syntax Error 
		// 	// return 258 in the Last exit status 
		// 	// free
		// }
		// // the token list looks like this:  ["echo" (WORD), "Hello $USER" (WORD), ">" (REDIR_OUT), "output.txt" (WORD)]
		
		
		free(line);
	}

	return (0);
}

