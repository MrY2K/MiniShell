/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/05/27 14:09:17 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token *cur_node)
{
	return ((cur_node)->type == '>' || (cur_node)->type == '<'
		|| (cur_node)->type == TOKEN_REDIR_APPEND || (cur_node)->type == TOKEN_HEREDOC);
}

int	special_char(t_token *token)
{
	return ((token->type != ' ' && token->type != TOKEN_WORD && token->type != '$'
		&& token->type != '\'' && token->type != '\"' && token->type != TOKEN_HEREDOC));
}

void	normal_cases(t_token **middle)
{
	// Case 1: Normal Command Tokens //  we  Inside double  /  single quotes and we have alpha char echo "hello world"
	if ((*middle) && special_char(*middle) && (*middle)->state != Normal)
	{
		while ((*middle) && (special_char(*middle) && (*middle)->state != Normal))
			(*middle) = (*middle)->next;
	}
	// case 2  We're inside quotes and token is a special character  echo "value: $PATH"  echo 'hello $USER'
	else if (((*middle) != NULL) && !special_char(*middle) && (*middle)->state != Normal)
	{
		while ((*middle) && !special_char(*middle) && (*middle)->state != Normal)
			(*middle) = (*middle)->next;
	}
	else if ((*middle) && (*middle)->state == Normal)
		(*middle) = (*middle)->next;
}

int	check_middle_syntax(t_token **middle)
{
	while ((*middle))
	{
		skip_spaces(&(*middle));
		// Case 1: Redirection operator found
		if ((*middle) && (*middle)->state == Normal &&  is_redirection((*middle)))
		{
			(*middle) = (*middle)->next; // Move past the redirection operator
			skip_spaces(&(*middle)); // Skip spaces after redirection
			if (!(*middle) || ((is_redirection(*middle) || (*middle)->type == '|') && (*middle)->state == Normal))
			{
				// echo hello >  echo hello > > file  echo hello > | grep  cat <<   cat <  echo hello >> < file   echo hello >>
				return (1);
			}
		}
		else if ((*middle) && (*middle)->type == '|' && (*middle)->state == Normal) // ls | |
		{
			(*middle) = (*middle)->next;
			skip_spaces(&(*middle)); // Skip spaces after redirection
			// Another pipe
			if (!(*middle) || ((*middle)->type == '|' && (*middle)->state == Normal))
				return (1);
		}
		else
			normal_cases(middle);
	}
	return (0);
}
