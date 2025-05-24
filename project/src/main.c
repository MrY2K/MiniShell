/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/24 17:31:22 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "lib/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
// #include "/goinfre/achoukri/homebrew/opt/readline/include/readline/readline.h"

char **split_tokens(const char *line);
void	ll(void) { system("leaks -q minishell"); }

typedef enum e_tokentype 
{
    T_WORD,
    T_PIPE,
    T_REDIR_IN,    // <
    T_REDIR_OUT,   // >
    T_HEREDOC,     // <<
    T_APPEND,      // >>
	//...
	
}   t_tokentype;

typedef struct	s_token 
{
	t_tokentype	type;
	char		*value;
}	t_token;

int ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

static volatile sig_atomic_t g_sig = 0;   // the *one* global

/* SIGINT handler -- prints new prompt like Bash */
static void  sigint_handler(int signum)
{
    g_sig = signum;
    rl_on_new_line();          /* say “we’re on a new empty line” */    /*:contentReference[oaicite:6]{index=6}*/
    rl_replace_line("", 0);    /* clear current buffer               */    /*:contentReference[oaicite:7]{index=7}*/
    rl_redisplay();            /* show fresh prompt                  */    /*:contentReference[oaicite:8]{index=8}*/
}

static void sigterm_handler(int signum)
{
	
}

int main(void)
{
    signal(SIGINT,  sigint_handler);   /* Ctrl-C  */            /*:contentReference[oaicite:9]{index=9}*/
    signal(SIGQUIT, SIG_IGN);          /* Ctrl-\  */
    char *line;

    while (1)
    {
        line = readline("minishell$ ");                           /*:contentReference[oaicite:10]{index=10}*/
        if (!line)        /* Ctrl-D: readline returns NULL */
            break;
        if (*line)        /* non-empty → remember it      */
            add_history(line);                                   /*:contentReference[oaicite:11]{index=11}*/

        /* …call your tokenizer / parser here… */

        free(line);
    }
    rl_clear_history();                                            /*:contentReference[oaicite:12]{index=12}*/
    write(1, "exit\n", 5);
    return (0);
}



// char **split_tokens(const char *line)
// {
// 	int i = 0;
// 	while (line[i])
// 	{
// 		// 1. skip whitespace
// 		while (line[i] && ft_isspace(line[i]))
// 			i++;

// 		if (!line[i])
// 			break;

// 		// 2. mark token start
// 		start = i;

// 		// 3. advance to token end
// 		while (line[i] && !ft_isspace(line[i]) && !is_metachar(line[i]))
// 			i++;

// 		// 4. extract substring line[start..i)
// 		token = ft_substr(...)
// 		append_token(token_array, token);
// 	}
// 	// 5. terminate array with NULL

// }

// static volatile sig_atomic_t g_sig = 0;   // the *one* global

// /* SIGINT handler -- prints new prompt like Bash */
// static void  sigint_handler(int signum)
// {
//     g_sig = signum;
// 	write(1, "\n", 1);           // ← explicit newline
//     rl_on_new_line();          /* say “we’re on a new empty line” */
//     rl_replace_line("", 0);    /* clear current buffer            */
//     rl_redisplay();            /* show fresh prompt               */
// }

// // void	init_sigaction(void)
// // {
// // }

// int main(void)
// {
// 	atexit(ll);
// 	// init_sigaction();
// 	signal(SIGINT,  sigint_handler);   /* Ctrl-C  */
// 	signal(SIGQUIT, SIG_IGN);          /* Ctrl-\  */
//     char *line;

//     while (1)
//     {
//         line = readline("minishell$ ");
//         if (!line)        /* Ctrl-D: readline returns NULL */
//             break;
//         if (*line)        /* non-empty → remember it       */
//             add_history(line);

//         /* …call your tokenizer / parser here… */

//         free(line);
//     }
//     rl_clear_history();
//     write(1, "exit\n", 5);
//     return (0);
// }
