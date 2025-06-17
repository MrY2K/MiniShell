#include "../../includes/minishell.h"
#include "../../includes/structs.h"

/*
* Process a segment of tokens until a pipe is encountered.
* It skips whitespace and non-word tokens and adds valid tokens
* by calling handle_token_part().
*/

void	process_non_pipe_segment(t_cmd **cmd_node, t_token **t_ptr,
	t_env *env, t_minibash b)
{
	char	**accumulated;

	accumulated = NULL;
	while ((*t_ptr) != NULL && !((*t_ptr)->type == '|'
			&& (*t_ptr)->state == Normal))
	{
		if ((*t_ptr) && (*t_ptr)->state == Normal
			&& ((*t_ptr)->type != -1 && (*t_ptr)->type != '$'))
			skip_nonword_tokens(t_ptr, env, b);
		if ((*t_ptr) && !((*t_ptr)->type == ' '
				&& (*t_ptr)->state == Normal))
			handle_token_part(cmd_node, t_ptr, env, &accumulated, b);
		if ((*t_ptr) && ((*t_ptr)->type == ' '
				&& (*t_ptr)->state == Normal))
			skip_whitespace(t_ptr);
	}
}

/*
* Check for adjacent empty quotes and update the command's args.
*/
int	check_empty_case(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
	if ((*tok_ptr) && (*tok_ptr)->next && ((*tok_ptr)->state == Normal
			&& (*tok_ptr)->next->state == Normal)
		&& (((*tok_ptr)->type == '\"' && (*tok_ptr)->next->type == '\"')
			|| ((*tok_ptr)->type == '\'' && (*tok_ptr)->next->type == '\'')))
	{
		(*tok_ptr) = (*tok_ptr)->next;
		(*tok_ptr) = (*tok_ptr)->next;
		join_to_arg_array(arg_arr, "");
		if ((*arg_arr)[0])
		{
			(*cmd_node)->argument = ft_join_arg((*cmd_node)->argument, *arg_arr);
			free_argument_array(*arg_arr);
			*arg_arr = NULL;
		}
		(*cmd_node)->next = NULL;
		return (1);
	}
	return (0);
}

// /*
// * Check for repeating quotes value sequence.
// */
int	check_repeating_quote(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
	while ((*tok_ptr) && (*tok_ptr)->next
		&& ((*tok_ptr)->state == Normal && (*tok_ptr)->next->state == Normal)
		&& (((*tok_ptr)->type == '\"' && (*tok_ptr)->next->type == '\"')
			|| ((*tok_ptr)->type == '\'' && (*tok_ptr)->next->type == '\''))
		&& ((*tok_ptr)->next->next
			&& (is_redirection((*tok_ptr)->next->next) != 1
				&& (*tok_ptr)->next->next->type != ' ')))
	{
		(*tok_ptr) = (*tok_ptr)->next;
		(*tok_ptr) = (*tok_ptr)->next;
	}
	if (check_empty_case(arg_arr, cmd_node, tok_ptr))
		return (1);
	return (0);
}

/*
* Process general word tokens and quoted strings.
*/

int	check_general_quote(t_cmd **cmd_node, t_token **tok_ptr,
		t_env *env, char ***arg_arr, t_minibash b)
{
	if ((*tok_ptr) && (*tok_ptr)->state == Normal && (*tok_ptr)->type != '\"'
		&& (*tok_ptr)->type != '\'' && (*tok_ptr)->type != '|' && (*tok_ptr)->type != ' ')
	{
		process_word(tok_ptr, env, 1, arg_arr, b);
		if (*arg_arr && (*arg_arr)[0])
		{
			(*cmd_node)->argument = ft_join_arg((*cmd_node)->argument, *arg_arr);
			free_argument_array(*arg_arr);
			*arg_arr = NULL;
		}
		return (1);
	}
	else if ((*tok_ptr) && (((*tok_ptr)->state == Double) || ((*tok_ptr)->state == Single)))
	{
		process_quoted(tok_ptr, env, 1, arg_arr, b);
		if (*arg_arr && (*arg_arr)[0])
		{
			(*cmd_node)->argument = ft_join_arg((*cmd_node)->argument, *arg_arr);
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
		t_env *env, char ***arg_arr, t_minibash b)
{
	if (check_repeating_quote(arg_arr, cmd_node, tok_ptr))
		return ;
	if (check_general_quote(cmd_node, tok_ptr, env, arg_arr, b))
		return ;
	else if ((*tok_ptr) && (*tok_ptr)->type != '|')
		*tok_ptr = (*tok_ptr)->next;
}
