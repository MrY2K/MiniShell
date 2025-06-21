/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:45:17 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:51 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
   Case 1: Opening double quote -> echo "hello
   Case 2: Closing double quote -> "hello"
   Case 3: Inside double quotes -> "hello"
   Case 4: Normal character -> echo hello  
   Case 5: Opening single quote -> echo 'hello
   Case 6: Closing single quote -> 'hello'
   Case 7: Inside single quotes -> 'hello'
*/

t_state	get_state(char c, t_lexer_state *ls)
{
	if (ls->double_q == -1 && ls->single_q == -1 && c == '\"')
		return (ls->double_q = 1, N);
	else if (ls->double_q == 1 && ls->single_q == -1 && c == '\"')
		return (ls->double_q = -1, N);
	else if (ls->double_q == 1 && ls->single_q == -1 && ft_isprint(c))
		return (D);
	else if (ls->double_q == -1 && ls->single_q == -1 
		&& c != '\'' && ft_isprint(c))
		return (N);
	else if (ls->double_q == -1 && ls->single_q == -1 && c == '\'')
		return (ls->single_q = 1, N);
	else if (ls->double_q == -1 && ls->single_q == 1 && c == '\'')
		return (ls->single_q = -1, N);
	else if (ls->double_q == -1 && ls->single_q == 1 && ft_isprint(c))
		return (S);
	return (NUL);
}

void	handle_word(char *input, t_lexer_state *ls, t_token **tokens)
{
	char	*value;

	while (input[ls->i] && !is_metachar(input[ls->i]))
	{
		ls->state = get_state(input[ls->i], ls);
		ls->i++;
		ls->len++;
	}
	value = ft_substr(input, ls->start, ls->len);
	ft_lstadd_back_token(tokens, ft_lstnew_token(value, ls->len,
			TOKEN_WORD, ls->state));
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
	if (check_middle_syntax(&start, N))
	{
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
		if (input[ls.i] && !is_metachar(input[ls.i]))
			handle_word(input, &ls, tokens);
		else if (input[ls.i] && is_metachar(input[ls.i]))
			handle_metachar(input, &ls, tokens);
	}
	if (is_syntax_error(tokens) || ls.double_q == 1 || ls.single_q == 1)
		return (1);
	return (0);
}
