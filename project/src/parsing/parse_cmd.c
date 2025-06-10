#include "../../includes/minishell.h"
# include "../../includes/structs.h"



#include <stdlib.h>
#include <string.h>

void debug_print_command(t_cmd *cmd);

// structure for combining arguments.
typedef struct s_ps
{
    int		idx;
    int		j;
    int		arg_len;
    int		join_len;
    char	**new_args;
}				t_ps;



/*
 * this bad boy here builds the command
 */
void	parse_input_commands(t_token **token_list, t_cmd **cmd_list, t_env *env)
{
    t_token	*cur_token;

    cur_token = *token_list;
    while (cur_token != NULL)
    {
        append_command(cmd_list, create_new_command(&cur_token, env));
    }
    /* Process any redirections. This is equivalent to ft_fill_red */
    process_redirections(cmd_list, token_list, env);
}

/*
 * Append a new command node to the command list.
 */
void	append_command(t_cmd **cmd_list, t_cmd *new_cmd)
{
    t_cmd	*last;

    if (!cmd_list || !new_cmd)
        return ;
    if (!*cmd_list)
        *cmd_list = new_cmd;
    else
    {
        last = last_command(*cmd_list);
        last->next = new_cmd;
    }
}

/*
 * Returns the last command value the list.
 */
t_cmd	*last_command(t_cmd *cmd_list)
{
    t_cmd	*last;

    last = cmd_list;
    if (!cmd_list)
        return (NULL);
    while (last->next != NULL)
        last = last->next;
    return (last);
}

/*
 * Create a new command node from the tokens.
 * If the current token is a pipe, mark pipe and advance.
 * Otherwise, process the command segment.
 */
t_cmd	*create_new_command(t_token **tok_ptr, t_env *env)
{
    t_cmd	*node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->argument = NULL;
    node->main_cmd = NULL;
    node->arg_len = 0;
    node->pipe = 0;
    node->redirections = NULL;
    node->heredoc= NULL;
    node->env_arr = NULL;

	if ((*tok_ptr) != NULL && ((*tok_ptr)->type == '|' && (*tok_ptr)->state == Normal))
	{
		join_to_arg_array(&(node->argument), (*tok_ptr)->value);
		node->pipe = 1;
		*tok_ptr = (*tok_ptr)->next;
	}
	else if ((*tok_ptr) != NULL)
		process_non_pipe_segment(&node, tok_ptr, env);
	if (node->argument && node->argument[0])
		node->main_cmd = node->argument[0];
	node->next = NULL;
    return (node);
}

/*
 * Append the token string to the command's argument array.
 */
void	join_to_arg_array(char ***arg_arr, char *tok_str)
{
    int		current_len;
    char	*dup;

    current_len = get_arg_count(*arg_arr);
    if (!tok_str)
        return ;
    if (current_len == 0)
    {
        *arg_arr = malloc(2 * sizeof(char *));
        (*arg_arr)[0] = ft_strdup(tok_str);
        (*arg_arr)[1] = NULL;
    }
    else
    {
        dup = ft_strdup(tok_str);
        current_len--;
        (*arg_arr)[current_len] = ft_strjoin((*arg_arr)[current_len], dup);
        free(dup);
    }
}

/*
 * Process a segment of tokens until a pipe is encountered.
 * It skips whitespace and non-word tokens and adds valid tokens
 * by calling handle_token_part().
 */
void	process_non_pipe_segment(t_cmd **cmd_node, t_token **tok_ptr, t_env *env)
{
    char	**accumulated = NULL;

    while ((*tok_ptr) != NULL && !((*tok_ptr)->type == '|' && (*tok_ptr)->state == Normal))
    {
        if ((*tok_ptr) && (*tok_ptr)->state == Normal &&
            ((*tok_ptr)->type != -1 && (*tok_ptr)->type != '$'))
            skip_nonword_tokens(tok_ptr, env);
        if ((*tok_ptr) && !((*tok_ptr)->type == ' ' && (*tok_ptr)->state == Normal))
            handle_token_part(cmd_node, tok_ptr, env, &accumulated);
        if ((*tok_ptr) && ((*tok_ptr)->type == ' ' && (*tok_ptr)->state == Normal))
            skip_whitespace(tok_ptr);
    }
}

/*
 * Check for adjacent empty quotes and update the command's args.
 */
int	check_empty_case(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
    if ((*tok_ptr) && (*tok_ptr)->next && ((*tok_ptr)->state == Normal && (*tok_ptr)->next->state == Normal)
        && (((*tok_ptr)->type == '\"' && (*tok_ptr)->next->type == '\"')
            || ((*tok_ptr)->type == '\'' && (*tok_ptr)->next->type == '\'')))
    {
        *tok_ptr = (*tok_ptr)->next;
        *tok_ptr = (*tok_ptr)->next;
        join_to_arg_array(arg_arr, "");
        if ((*arg_arr)[0])
        {
            (*cmd_node)->argument = combine_arguments((*cmd_node)->argument, *arg_arr);
            free_argument_array(*arg_arr);
            *arg_arr = NULL;
        }
        (*cmd_node)->next = NULL;
        return (1);
    }
    return (0);
}

/*
 * Check for repeating quotes value sequence.
 */
int	check_repeating_quote(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
    while ((*tok_ptr) && (*tok_ptr)->next &&
        ((*tok_ptr)->state == Normal && (*tok_ptr)->next->state == Normal) &&
        (((*tok_ptr)->type == '\"' && (*tok_ptr)->next->type == '\"')
            || ((*tok_ptr)->type == '\'' && (*tok_ptr)->next->type == '\'')) &&
        ((*tok_ptr)->next->next && (is_redirection((*tok_ptr)->next->next) != 1
            && (*tok_ptr)->next->next->type != ' ')))
    {
        *tok_ptr = (*tok_ptr)->next;
        *tok_ptr = (*tok_ptr)->next;
    }
    if (check_empty_case(arg_arr, cmd_node, tok_ptr))
        return (1);
    return (0);
}

/*
 * Process general word tokens and quoted strings.
 */
int	check_general_quote(t_cmd **cmd_node, t_token **tok_ptr,
        t_env *env, char ***arg_arr)
{
    if ((*tok_ptr) && (*tok_ptr)->state == Normal && (*tok_ptr)->type != '\"'
        && (*tok_ptr)->type != '\'' && (*tok_ptr)->type != '|')
    {
        process_word(tok_ptr, env, 1, arg_arr);
        if (*arg_arr && (*arg_arr)[0])
        {
            (*cmd_node)->argument = combine_arguments((*cmd_node)->argument, *arg_arr);
            free_argument_array(*arg_arr);
            *arg_arr = NULL;
        }
        return (1);
    }
    else if ((*tok_ptr) && (((*tok_ptr)->state == Double) || ((*tok_ptr)->state == Single)))
    {
        process_quoted(tok_ptr, env, 1, arg_arr);
        if (*arg_arr && (*arg_arr)[0])
        {
            (*cmd_node)->argument = combine_arguments((*cmd_node)->argument, *arg_arr);
            free_argument_array(*arg_arr);
            *arg_arr = NULL;
        }
        return (1);
    }
    return (0);
}

/*
 * Process a single token group.
 */
void	handle_token_part(t_cmd **cmd_node, t_token **tok_ptr,
        t_env *env, char ***arg_arr)
{
    if (check_repeating_quote(arg_arr, cmd_node, tok_ptr))
        return ;
    if (check_general_quote(cmd_node, tok_ptr, env, arg_arr))
        return ;
    else if ((*tok_ptr) && (*tok_ptr)->type != '|')
        *tok_ptr = (*tok_ptr)->next;
}

/*
 * Free the argument array.
 */
void	free_argument_array(char **arr)
{
    int	i = 0;

    if (!arr)
        return ;
    while (arr[i])
    {
        free(arr[i]);
        arr[i] = NULL;
        i++;
    }
    free(arr);
    arr = NULL;
}

/*
 * Returns 1 if the token represents a redirection.
 */
// int	is_redirection(t_token *node)
// {
//     if (node->type == '<' || node->type == '>' ||
//         node->type == TOKEN_REDIR_APPEND || node->type == TOKEN_HEREDOC)
//         return (1);
//     return (0);
// }

/*
 * Combine two arrays of arguments.
 */
char	**combine_arguments(char **args, char **addition)
{
    t_ps	ps;

    ps.idx = 0;
    ps.j = 0;
    ps.arg_len = get_arg_count(args);
    ps.join_len = get_arg_count(addition);
    ps.new_args = malloc(((ps.arg_len + ps.join_len) + 1) * sizeof(char *));
    ps.new_args[0] = NULL;
    if (args)
    {
        while (args[ps.idx])
        {
            ps.new_args[ps.j] = ft_strdup(args[ps.idx]);
            ps.j++;
            ps.idx++;
        }
    }
    ps.idx = 0;
    while (addition && addition[ps.idx])
        ps.new_args[ps.j++] = ft_strdup(addition[ps.idx++]);
    ps.new_args[ps.j] = NULL;
    free_argument_array(args);
    return (ps.new_args);
}

/*
 * Skip all whitespace tokens.
 */
void	skip_whitespace(t_token **tok_ptr)
{
    while ((*tok_ptr) && (*tok_ptr)->type == ' ')
        *tok_ptr = (*tok_ptr)->next;
}

/*
 * Skip non-word tokens (like redirection tokens) and process their main_cmd.
 */
void	skip_nonword_tokens(t_token **tok_ptr, t_env *env)
{
    char	**tempArr = NULL;

    while ((*tok_ptr) && (((*tok_ptr)->type == '<') ||
            ((*tok_ptr)->type == '>') || ((*tok_ptr)->type == TOKEN_REDIR_APPEND) ||
            ((*tok_ptr)->type == TOKEN_HEREDOC)))
    {
        *tok_ptr = (*tok_ptr)->next;
        skip_whitespace(tok_ptr);
        while ((*tok_ptr) && (*tok_ptr)->state == Normal &&
            (((*tok_ptr)->type == '\"') || ((*tok_ptr)->type == '\'')))
            *tok_ptr = (*tok_ptr)->next;
        if ((*tok_ptr) && (*tok_ptr)->state == Normal &&
            ((*tok_ptr)->type != '\"') && ((*tok_ptr)->type != '\'') &&
            ((*tok_ptr)->type != '|'))
            process_word(tok_ptr, env, 0, &tempArr);
        else if ((*tok_ptr) && (((*tok_ptr)->state == Double) || ((*tok_ptr)->state == Single)))
            process_quoted(tok_ptr, env, 0, &tempArr);
    }
    free_args(tempArr);
}


void	process_word(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr)
{
	(void)env; //for now
	(void)flag; //for now
    /* Dummy implementation: simply add the token's string */
    char *temp = ft_strdup((*tok_ptr)->value);
    if (!*arg_arr)
    {
        *arg_arr = malloc(2 * sizeof(char *));
        (*arg_arr)[0] = temp;
        (*arg_arr)[1] = NULL;
    }
    else
    {
        int arg_len = get_arg_count(*arg_arr);
        (*arg_arr)[arg_len - 1] = ft_strjoin((*arg_arr)[arg_len - 1], temp);
        free(temp);
    }
    *tok_ptr = (*tok_ptr)->next;
}

void	process_quoted(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr)
{
    /* Dummy implementation: treat quoted token like a word */
    process_word(tok_ptr, env, flag, arg_arr);
}

void	free_args(char **args)
{
    free_argument_array(args);
}

void	process_redirections(t_cmd **cmd_list, t_token **tokens, t_env *env)
{
    /* Dummy implementation for redirection handling */
    (void)cmd_list;
    (void)tokens;
    (void)env;
}
