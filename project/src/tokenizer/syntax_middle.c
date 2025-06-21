/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_middle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:17:12 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/20 17:21:04 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token *cur_node)
{
	return ((cur_node)->type == '>' || (cur_node)->type == '<'
		|| (cur_node)->type == TOKEN_REDIR_APPEND
		|| (cur_node)->type == TOKEN_HEREDOC);
}

/* special_char  : > < |  && || >> */

int	special_char(t_token *token)
{
	return ((token->type != ' ' && token->type != TOKEN_WORD
			&& token->type != '$' && token->type != '\'' && token->type != '\"'
			&& token->type != TOKEN_HEREDOC));
}
/*
	Case 1: Normal Command Tokens //  we  Inside double
		/  single quotes and we have alpha char echo "hello  world"
	
	case 2  We're inside quotes and token is a special character  
		echo "value: $PATH"  echo 'hello $USER' echo 'hi | hej'
	
*/

void	normal_cases(t_token **middle)
{
	if (!*middle)
		return ;
	if ((*middle) && special_char(*middle) && (*middle)->state != Normal)
	{
		while ((*middle) && (special_char(*middle)
				&& (*middle)->state != Normal))
			(*middle) = (*middle)->next;
	}
	else if (((*middle) != NULL) && !special_char(*middle)
		&& (*middle)->state != Normal)
	{
		while ((*middle) && !special_char(*middle)
			&& (*middle)->state != Normal)
			(*middle) = (*middle)->next;
	}
	else if ((*middle) && (*middle)->state == Normal)
		(*middle) = (*middle)->next;
}

/*
	case 1 :
		echo hello >
		echo hello > > file   echo hello >> < file
		echo hello > | grep
	
	case 2 :
			ls |
			ls | | grep
		
		
*/
int	check_middle_syntax(t_token **middle, enum e_state NOR)
{
	while ((*middle))
	{
		skip_spaces(&(*middle));
		if ((*middle) && is_redirection((*middle))
			&& (*middle)->state == Normal)
		{
			(*middle) = (*middle)->next;
			skip_spaces(&(*middle));
			if (!(*middle) || ((is_redirection(*middle)
						|| (*middle)->type == '|') && (*middle)->state == NOR))
				return (1);
		}
		else if ((*middle)
			&& (*middle)->type == '|' && (*middle)->state == Normal)
		{
			(*middle) = (*middle)->next;
			skip_spaces(&(*middle));
			if (!(*middle)
				|| ((*middle)->type == '|' && (*middle)->state == Normal))
				return (1);
		}
		else
			normal_cases(middle);
	}
	return (0);
}
