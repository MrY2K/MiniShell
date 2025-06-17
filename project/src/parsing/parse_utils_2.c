#include "../../includes/minishell.h"

void	skip_nonword_tokens(t_token **tok_ptr, t_env *env, t_minibash b)
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
			process_word(tok_ptr, env, 0, &arr, b);
		else if ((*tok_ptr) && (((*tok_ptr)->state == Double)
				|| ((*tok_ptr)->state == Single)))
			process_quoted(tok_ptr, env, 0, &arr, b);
	}
	free_argument_array(arr);
}
