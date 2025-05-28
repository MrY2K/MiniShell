#include "../../includes/minishell.h"

t_state	get_state(char c, t_lexer_state *ls)
{
	if (ls->double_q == -1 && ls->single_q == -1 && c == '\"')
		return (ls->double_q = 1, Normal); // Enter double-quote mode -> " echo "
	else if (ls->double_q == 1 && ls->single_q == -1 && c == '\"')
		return (ls->double_q = -1, Normal); // close double-quote "..."
	else if (ls->double_q  == 1 && ls->single_q == -1 && ft_isprint(c))
		return (Double); // we're inside double quotes "..
	else if (ls->double_q == -1 && ls->single_q == -1 && c != '\'' && ft_isprint(c))
		return (Normal); // we're not in any quotes  h e l l o
	else if (ls->double_q == -1 && ls->single_q == -1 && c == '\'')
		return (ls->single_q = 1, Normal); // single quote echo '
	else if (ls->double_q == -1 && ls->single_q == 1 && c == '\'')
		return (ls->single_q = -1, Normal); // closing single quotes
	else if (ls->double_q == -1 && ls->single_q == 1 && ft_isprint(c))
		return (Single); // we're inside single quote 
	else if (ls->double_q == -1 && ls->single_q == -1 && ft_isprint(c) && c != '\"')
		return (Normal); // $ 5
	return (NUL);
}

void handle_word(char *input, t_lexer_state *ls, t_token **tokens)
{
	char *value;
	int	i;

	i = 0;
	while (input[ls->i] && !is_metachar(input[ls->i]))
	{
		ls->state = get_state(input[ls->i], ls);
		ls->i++;
		ls->len++;
		i++;
	}
	value = ft_substr(input, ls->start, ls->len);
	ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len, TOKEN_WORD, ls->state));
}

// *********   handell char ✅   ✅    ✅   ✅ 

void	env_variables(char *input, t_lexer_state *ls)
{
	// Case 1: Numeric variables $1, $2
	if (ft_isdigit(input[ls->i + 1]))
	{
		ls->state = get_state(input[ls->i++], ls);
		ls->len++;
	}
	else // Alphanumeric
	{
		while (input[ls->i] && input[ls->i + 1] && !is_metachar(input[ls->i + 1]) && ft_isalnum(input[ls->i + 1]))
		{
			ls->state = get_state(input[ls->i], ls);
			ls->len++;
		}
	}
}

void	shell_variable(char *input, t_lexer_state *ls)
{
	// $1 $HOME   $PATH 
	if (input[ls->i] && input[ls->i] == '$' && input[ls->i + 1] &&  ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))
	{
		env_variables(input, ls);
	}
	else if (input[ls->i] && input[ls->i] == '$' && input[ls->i + 1] && input[ls->i + 1] == '?') // $? Exit Status
	{
		ls->state = get_state(input[ls->i], ls);
		ls->i++;
		ls->len++;
	}
	else if (input[ls->i] && input[ls->i] == '$' && !ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))// Invalid/Edge Cases $@, $#
	{
		while (input[ls->i] && input[ls->i] == '$' && !ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))
		{
			ls->state = get_state(input[ls->i], ls);
			ls->len++;
		}
	}
	else
		ls->state = get_state(input[ls->i], ls); // $$ $> $" $ (space)  $| 
}

void	handle_env_variables(char *input, t_lexer_state *ls, t_token **tokens)
{
	char	*value;

	 // Handles cases like $"" or $''
	if ((input[ls->i] && input[ls->i + 1] && input[ls->i + 2] && input[ls->i] == '$')
		&& ((input[ls->i + 1] == '\"' && input[ls->i + 2] == '\"') || (input[ls->i + 1] == '\'' && input[ls->i + 2] == '\'')))
	{
		ls->state = Normal;
		ls->i += 3;
		ls->len += 3;
	}
	// Handles cases like $" or $' but not closed
	else if ((input[ls->i] && input[ls->i + 1] && input[ls->i + 2] && input[ls->i] == '$')
		&& ((input[ls->i + 1] == '\"') || (input[ls->i + 1] == '\'')) && (input[ls->i
				+ 2] != '\'' || input[ls->i + 2] != '\"'))
	{
		ls->i++; // Move past the '$' to the quote character
		ls->state= get_state(input[ls->i], ls); // Update lexer state based on quote type
		ls->len++;// Increment the length counter
	}
	else // handell $? $PATH
		shell_variable(input, ls);
	value = ft_substr(input, ls->start, ls->len);
	ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len, TOKEN_ENV, ls->state));
	free(value);
}

void	handell_append_herdoc(t_token **tokens, char *input, t_lexer_state *ls)
{
	char	*value;

	ls->i++;
	ls->len++;
	if (input[ls->i] == '>')
	{
		value = ft_substr(input, ls->start, ls->len);
		ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len, TOKEN_REDIR_APPEND, ls->state));
		free(value);
	}
	else if (input[ls->i] == '<')
	{
		value = ft_substr(input, ls->start, ls->len);
		ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len, TOKEN_HEREDOC, ls->state));
		free(value);
	}
}


t_token_type	get_token_type(char c)
{
	if (c == '$')
		return (TOKEN_ENV);
	else if (c == '|')
		return (TOKEN_PIPE);
	else if (c == '\n')
		return (TOKEN_NEWLINE);
	else if (c == '\'')
		return (TOKEN_SINGLE_QUOTE);
	else if (c == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	else if (c == '>')
		return (TOKEN_REDIR_OUT);
	else if (c == '<')
		return (TOKEN_REDIR_IN);
	else if (c == ' ' || c == '\t' || c == '\n')
		return (TOKEN_WHITE_SPACE);
	return (0);

}

void	handle_metachar(char *input, t_lexer_state *ls, t_token **tokens)
{
	char *value;

	ls->len++;
	if (input[ls->i] && input[ls->i] == '$') // handell env variables $
		handle_env_variables(input, ls, tokens);
		// >> append  and   << here doc
	else
	{
		if (input[ls->i] && ((input[ls->i] == '>' && input[ls->i + 1] && input[ls->i + 1] == '>')
			|| (input[ls->i] == '<' && input[ls->i + 1] && input[ls->i + 1] == '<')))
		{
			handell_append_herdoc(tokens, input, ls);
		}
		else // all case like > - Output redirection  < - Input redirection ' or "   |  
		{
			value = ft_substr(input, ls->start, ls->len);
			ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len,get_token_type(input[ls->i]) , get_state(input[ls->i], ls)));
		}
	}
	ls->i++;
}
// ******* ✅   ✅   ✅   ✅  handell syntax error  ✅   ✅    ✅   ✅  *************** 


void	skip_spaces(t_token	**cur_node)
{
	while ((*cur_node) && (*cur_node)->type == 32)
	{
		(*cur_node) = (*cur_node)->next;
	}
}

t_token	*last_node(t_token *lst)
{
	t_token	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

int	is_syntax_error(t_token **tokens)
{
	t_token	*start;
	t_token	*last;

	if (!tokens || !(*tokens))
		return (0);
	start = *tokens;
	skip_spaces(&start);

	if (has_syntax_error_at_start(&start))
	{

		return (1);
	}
	if (check_middle_syntax(&start))
	{
		//ft_putendl_fd("minishell: syntax error", 2);
		return (1);
	}
	start = *tokens;
	last = last_node(start);
	if (last && last->type == '|')
	{
		return (1);
	}
	return (0);
}

int	lexer(char *input, t_token **tokens)
{
	t_lexer_state	ls;
	int				len;

	if (!input || !tokens)
		return (1);
	len = ft_strlen(input);
	ls.i = 0;
	ls.double_q = -1;
	ls.single_q = -1;
	while (ls.i < len)
	{
		ls.start = ls.i;
		ls.len = 0;
		// else if (input[ls.i] && !is_metachar(input[ls.i]))
		// 	handle_word(input, &ls, tokens);// start with string 
		if (input[ls.i] && !is_metachar(input[ls.i]))
    		handle_word(input, &ls, tokens);
		else if (input[ls.i] && is_metachar(input[ls.i]))
			handle_metachar(input, &ls, tokens); // start with char / < .. 
	}
	// handell syntax error 
	if (is_syntax_error(tokens) ||  ls.double_q == 1 || ls.single_q == 1)
		return (1);
	return (0);
}
