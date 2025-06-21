/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:43:22 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/21 02:31:37 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handell_append_herdoc(t_token **tokens, char *input, t_lexer_state *ls)
{
	char	*value;

	ls->i++;
	ls->len++;
	if (input[ls->i] == '>')
	{
		value = ft_substr(input, ls->start, ls->len);
		ft_lstadd_back_token(tokens, ft_lstnew_token(
				value, ls->len, TOKEN_REDIR_APPEND,
				get_state(input[ls->i], ls)));
	}
	else if (input[ls->i] == '<')
	{
		value = ft_substr(input, ls->start, ls->len);
		ft_lstadd_back_token(tokens, ft_lstnew_token(
				value, ls->len, TOKEN_HEREDOC,
				get_state(input[ls->i], ls)));
	}
}

/*
	$1, $2  ->  Positional arguments
		bash -c 'echo $1 ....  $2' _  hej ajelloul
			result : hej .... ajelloul
		_ : used as the first argument ($0)

		bash -c 'echo $0 $1 $2' _ HEJ HOW
			result : _ HEJ HOW

	$*  -> All arguments as a single string
		bash -c 'echo $*' _ hej ajelloul
			result : hej ajelloul


	$# → Number of arguments
		bash -c 'echo $#' _ hej hello bonjour
			result : 3

	$@ → All arguments separately (preserves quotes)
		bash -c 'for arg in "$@"; do echo "$arg"; 
				done' _ Salam_Alukoum  Hej hello
			Salam_Alukoum
			Hej
			hello
		bash -c 'for arg in "$@"; do echo " -> $arg <- "; 
			done' _ Salam_Alukoum  Hej hello
			-> Salam_Alukoum <- 
			-> Hej <- 
			-> hello <- 
*/

void	env_variables(char *input, t_lexer_state *ls)
{
	if (input[ls->i] && ft_isdigit(input[ls->i + 1]))
	{
		ls->state = get_state(input[ls->i++], ls);
		ls->len++;
	}
	else
	{
		while (input[ls->i] && input[ls->i + 1]
			&& !is_metachar(input[ls->i + 1])
			&& ft_isalnum(input[ls->i + 1]))
		{
			ls->state = get_state(input[ls->i++], ls);
			ls->len++;
		}
	}
}
/*
	Case 1: environment variables -> $HOME $PATH $USER $1
		Result: Expands to variable value

	Case 2: Exit status -> $?
		Result: Expands to last command exit code

	Case 3: Invalid shell parameters -> $@ $# $*
		Result: Treated as invalid  no expansion

	Case 4: Dollar with special chars -> $$ ..
		Result: Dollar treated as literal character
*/

void	shell_variable(char *input, t_lexer_state *ls)
{
	if (input[ls->i] && input[ls->i] == '$'
		&& input[ls->i + 1]
		&& ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))
	{
		env_variables(input, ls);
	}
	else if (input[ls->i] && input[ls->i] == '$'
		&& input[ls->i + 1] && input[ls->i + 1] == '?')
	{
		ls->state = get_state(input[ls->i], ls);
		ls->i++;
		ls->len++;
	}
	else if (input[ls->i] && input[ls->i] == '$'
		&& !ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))
	{
		while (input[ls->i] && input[ls->i] == '$'
			&& !ft_isalnum(input[ls->i + 1]) && !is_metachar(input[ls->i + 1]))
		{
			ls->state = get_state(input[ls->i++], ls);
			ls->len++;
		}
	}
	else
		ls->state = get_state(input[ls->i], ls);
}

/*
   Case 1: Empty variable -> echo $""
	echo $"" -> results in empty string

   Case 2: Variable with quote -> echo $"PATH or echo $'PATH  
   	Description: $ followed by opening quote, 
		then variable name (no closing quote yet)
   	Example: echo $"PATH -> starts quoted variable expansion

   Case 3: Normal shell variables -> echo $PATH $HOME $? 
*/

void	handle_env_variables(char *input, t_lexer_state *ls, t_token **tokens)
{
	char	*value;

	if ((input[ls->i] && input[ls->i + 1]
			&& input[ls->i + 2] && input[ls->i] == '$')
		&& ((input[ls->i + 1] == '\"' && input[ls->i + 2] == '\"')
			|| (input[ls->i + 1] == '\'' && input[ls->i + 2] == '\'')))
	{
		ls->state = N;
		ls->i += 3;
		ls->len += 3;
	}
	else if ((input[ls->i] && input[ls->i + 1]
			&& input[ls->i + 2] && input[ls->i] == '$')
		&& ((input[ls->i + 1] == '\"') || (input[ls->i + 1] == '\''))
		&& (input[ls->i + 2] != '\'' || input[ls->i + 2] != '\"'))
	{
		ls->i++;
		ls->state = get_state(input[ls->i], ls);
		ls->len++;
	}
	else
		shell_variable(input, ls);
	value = ft_substr(input, ls->start, ls->len);
	ft_lstadd_back_token(tokens, ft_lstnew_token(
			value, ls->len, TOKEN_ENV, ls->state));
}
/*
   Case 1: Environment variables
   Case 2: Append/Heredoc >> >> 
   Case 3: Single metacharacters -> > <  | .. 
*/

void	handle_metachar(char *input, t_lexer_state *ls, t_token **tokens)
{
	char	*value;

	ls->len++;
	if (input[ls->i] && input[ls->i] == '$')
	{
		handle_env_variables(input, ls, tokens);
	}
	else
	{
		if (input[ls->i] && ((input[ls->i] == '>'
					&& input[ls->i + 1] && input[ls->i + 1] == '>')
				|| (input[ls->i] == '<'
					&& input[ls->i + 1] && input[ls->i + 1] == '<')))
		{
			handell_append_herdoc(tokens, input, ls);
		}
		else
		{
			value = ft_substr(input, ls->start, ls->len);
			ft_lstadd_back_token(tokens, ft_lstnew_token(
					value, ls->len,
					get_token_type(input[ls->i]), get_state(input[ls->i], ls)));
		}
	}
	ls->i++;
}
