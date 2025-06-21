/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 23:27:44 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


#include "../includes/minishell.h"


/* Debug print for the t_token linked list */
void debug_print_token_list(t_token *list)
{
    int idx = 0;
    while (list)
    {
        // Print index, value (in quotes), len, type, state
        // If value may contain non-printables, consider printing repr; here we assume printable.
        printf("Token[%d]: value=\"%s\" len=%d type=%d state=%d\n",
               idx,
               list->value ? list->value : "(null)",
               list->len,
               list->type,
               list->state);
        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no tokens)\n");
}

/* Helper to print a redirection type as string, if you wish */
static const char *redir_type_to_str(t_token_type type)
{
    // Adjust these cases according to your enum definitions
    if (type == '<')               return "<";
    if (type == '>')               return ">";
    if (type == TOKEN_REDIR_APPEND) return ">>";  // or your enum constant
    if (type == TOKEN_HEREDOC)     return "<<";  // or your enum constant
    // If type is stored differently, add cases here
    // Fallback:
    static char buf[8];
    if (type >= 32 && type < 127) {
        snprintf(buf, sizeof(buf), "%c", (char)type);
        return buf;
    }
    snprintf(buf, sizeof(buf), "%d", (int)type);
    return buf;
}

/* Debug print for the t_cmd linked list */
void debug_print_cmd_list(t_cmd *list)
{
    int idx = 0;
    while (list)
    {
        printf("=== Command[%d] ===\n", idx);
        // main_cmd
        if (list->main_cmd && *list->main_cmd)
            printf(" main_cmd: \"%s\"\n", list->main_cmd);
        else
            printf(" main_cmd: (null or empty)\n");
        // arguments array
        if (list->argument)
        {
            printf(" argv:");
            for (int i = 0; list->argument[i]; i++)
                printf(" [\"%s\"]", list->argument[i]);
            printf("\n");
        }
        else
        {
            printf(" argv: (none)\n");
        }
        // arg_len if meaningful
        printf(" arg_len: %d\n", list->arg_len);
        // flags
        printf(" has_ambiguous: %d\n", list->has_ambiguous);
        printf(" pipe: %d\n", list->pipe);
        printf(" needs_expansion: %d\n", list->needs_expansion);
        // environment array if present
        if (list->env_arr)
        {
            printf(" env_arr:");
            for (int i = 0; list->env_arr[i]; i++)
                printf(" [\"%s\"]", list->env_arr[i]);
            printf("\n");
        }
        else
            printf(" env_arr: (none)\n");
        // red
        if (list->red)
        {
            printf(" red:\n");
            for (t_redirect *r = list->red; r; r = r->next)
            {
                const char *sym = redir_type_to_str(r->type);
                printf("   %s  file=\"%s\"  is_ambiguous=%d\n",
                       sym,
                       r->file_path ? r->file_path : "(null)",
                       r->is_ambig);
            }
        }
        else
            printf(" red: (none)\n");
        // heredocs
        if (list->heredoc)
        {
            printf(" heredocs:\n");
            for (t_heredoc *h = list->heredoc; h; h = h->next)
            {
                printf("   delimiter=\"%s\"  her_file=\"%s\"  fd=%d  expand=%d\n",
                       h->delimiter ? h->delimiter : "(null)",
                       h->her_file ? h->her_file : "(null)",
                       h->fd,
                       h->expand);
            }
        }
        else
            printf(" heredocs: (none)\n");

        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no command nodes)\n");
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	execute_command_pipeline(t_minibash *bash, t_env **env,
	t_token *token, t_cmd **cmd)
{
	if (token && env)
	{
		debug_print_token_list(token); //? DEBUG
		parse_input_commands(&token, cmd, bash);
		debug_print_cmd_list(*cmd); //? DEBUG
		execution(bash, env, *cmd);
	}
	free_cmd_list(cmd);
	free_lexer(&token);
}

void	ft_readline(t_minibash	*bash, t_token *tokens, t_cmd *cmd, t_env **env)
{
	char	*line;

	while (true)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line && *line)
			add_history(line);
		if (lexer(line, &tokens))
		{
			ft_putendl_fd("minishell: syntax error", 2);
			bash->exit_status = 258;
			free_lexer(&tokens);
		}
		else
			execute_command_pipeline(bash, env, tokens, &cmd);
		tokens = NULL;
		cmd = NULL;
		free (line);
	}
	rl_clear_history();
	write(1, "exit\n", 5);
	exit (bash->exit_status);
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
	int			exit_st;

	(void)ac;
	(void)av;
	tokens = NULL;
	cmd = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_minibash(&bash);
	initialize_environment(bash, env);
	ft_readline(bash, tokens, cmd, &bash->env);
	exit_st = bash->exit_status;
	free_minibash(&bash);
	return (exit_st);
}
