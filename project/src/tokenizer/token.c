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
		return (Normal); // $
	return (NUL);
}

void handle_word(char *input, t_lexer_state *ls, t_token **tokens)
{
	char *value;
	int	i;

	i = 0;
	while (input[ls->i] && !is_metachar(input[ls->i]))
	{
		ls->i++;
		ls->len++;
		ls->state = get_state(input[ls->i], ls);
		i++;
	}
	value = ft_substr(input, ls->start, ls->len);
	ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len, TOKEN_WORD, ls->state));
}

void	handle_metachar(char *input, t_lexer_state *ls, t_token **tokens)
{
	(void)tokens;
	ls->len++;
	if ((input[ls->i] && input[ls->i + 1] && input[ls->i + 2] && input[ls->i] == '$') // echo $"" echo $''
		&& ((input[ls->i + 1] == '\"' && input[ls->i + 2] == '\"') || (input[ls->i + 1] == '\'' && input[ls->i + 2] == '\'')))
	{
		ls->state = get_state(input[ls->i], ls);
		ls->i += 3;
		ls->len += 3;
	}
	// handel
}

int	lexer(char *input, t_token **tokens)
{
	t_lexer_state	ls;
	int				input_len;

	if (!input || !tokens)
		return (1);
	input_len = ft_strlen(input);
	ls.i = 0;
	ls.double_q = -1;
	ls.single_q = -1;
	while (ls.i < input_len)
	{
		ls.start = ls.i;
		ls.len = 0;
		if (input[ls.i] && is_metachar(input[ls.i]))
			handle_metachar(input, &ls, tokens); // start with char / < .. 
		else if (input[ls.i] && !is_metachar(input[ls.i]))
			handle_word(input, &ls, tokens);// start with string 
		
		if (ls.len == 0)
        	ls.i++;
	}
	return (0);
}
