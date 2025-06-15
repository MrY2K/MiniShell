#include "../../includes/minishell.h"
#include "../../includes/structs.h"

/*
* Free the argument array.
*/
void	free_argument_array(char **arr)
{
	int	i;

	i = 0;
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
	char	**arr;

	arr = NULL;
	while ((*tok_ptr) && (((*tok_ptr)->type == '<')
			|| ((*tok_ptr)->type == '>')
			|| ((*tok_ptr)->type == TOKEN_REDIR_APPEND)
			|| ((*tok_ptr)->type == TOKEN_HEREDOC)))
	{
		*tok_ptr = (*tok_ptr)->next;
		skip_whitespace(tok_ptr);
		while ((*tok_ptr) && (*tok_ptr)->state == Normal
			&& (((*tok_ptr)->type == '\"') || ((*tok_ptr)->type == '\'')))
			*tok_ptr = (*tok_ptr)->next;
		if ((*tok_ptr) && (*tok_ptr)->state == Normal
			&& ((*tok_ptr)->type != '\"') && ((*tok_ptr)->type != '\'')
			&& ((*tok_ptr)->type != '|'))
			process_word(tok_ptr, env, 0, &arr);
		else if ((*tok_ptr) && (((*tok_ptr)->state == Double)
				|| ((*tok_ptr)->state == Single)))
			process_quoted(tok_ptr, env, 0, &arr);
	}
	free_args(arr);
}

void	process_word(t_token **tok_ptr, t_env *env, int flag, char ***arg_arr)
{
	char	*temp;
	int		arg_len;

	(void)env;
	(void)flag;
	temp = ft_strdup((*tok_ptr)->value);
	if (!*arg_arr)
	{
		*arg_arr = malloc(2 * sizeof(char *));
		(*arg_arr)[0] = temp;
		(*arg_arr)[1] = NULL;
	}
	else
	{
		arg_len = get_arg_count(*arg_arr);
		(*arg_arr)[arg_len - 1] = ft_strjoin((*arg_arr)[arg_len - 1], temp);
		free(temp);
	}
	*tok_ptr = (*tok_ptr)->next;
}
