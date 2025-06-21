/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:10:34 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:57:40 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_non_pipe_segment(t_cmd **cmd_node, t_token **t_ptr, t_minibash *b)
{
	char	**accumulated;

	(void)b;
	accumulated = NULL;
	while ((*t_ptr) != NULL && !((*t_ptr)->type == '|'
			&& (*t_ptr)->state == N))
	{
		if ((*t_ptr) && (*t_ptr)->state == N
			&& ((*t_ptr)->type != -1 && (*t_ptr)->type != '$'))
			skip_nonword_tokens(t_ptr, b);
		if ((*t_ptr) && !((*t_ptr)->type == ' '
				&& (*t_ptr)->state == N))
			handle_token_part(cmd_node, t_ptr, b, &accumulated);
		if ((*t_ptr) && ((*t_ptr)->type == ' '
				&& (*t_ptr)->state == N))
			skip_whitespace(t_ptr);
	}
}

int	check_empty_case(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
	if ((*tok_ptr) && (*tok_ptr)->next && ((*tok_ptr)->state == N
			&& (*tok_ptr)->next->state == N)
		&& (((*tok_ptr)->type == '\"' && (*tok_ptr)->next->type == '\"')
			|| ((*tok_ptr)->type == '\'' && (*tok_ptr)->next->type == '\'')))
	{
		(*tok_ptr) = (*tok_ptr)->next;
		(*tok_ptr) = (*tok_ptr)->next;
		join_to_arg_array(arg_arr, "");
		if ((*arg_arr)[0])
		{
			(*cmd_node)->argument = ft_join_arg((*cmd_node)->argument,
					*arg_arr);
			free_argument_array(*arg_arr);
			*arg_arr = NULL;
		}
		(*cmd_node)->next = NULL;
		return (1);
	}
	return (0);
}

int	check_repeating_quote(char ***arg_arr, t_cmd **cmd_node, t_token **tok_ptr)
{
	while ((*tok_ptr) && (*tok_ptr)->next
		&& ((*tok_ptr)->state == N && (*tok_ptr)->next->state == N)
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

int	check_general_quote(t_cmd **node, t_token **p,
		t_minibash *b, char ***arg_arr)
{
	if ((*p) && (*p)->state == N && (*p)->type != '\"'
		&& (*p)->type != '\'' && (*p)->type != '|' && (*p)->type != ' ')
	{
		process_word(p, b, 1, arg_arr);
		if (*arg_arr && (*arg_arr)[0])
		{
			(*node)->argument = ft_join_arg((*node)->argument, *arg_arr);
			free_argument_array(*arg_arr);
			*arg_arr = NULL;
		}
		return (1);
	}
	else if ((*p) && (((*p)->state == D) || ((*p)->state == S)))
	{
		process_quoted(p, b, 1, arg_arr);
		if (*arg_arr && (*arg_arr)[0])
		{
			(*node)->argument = ft_join_arg((*node)->argument, *arg_arr);
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
		t_minibash *b, char ***arg_arr)
{
	if (check_repeating_quote(arg_arr, cmd_node, tok_ptr))
		return ;
	if (check_general_quote(cmd_node, tok_ptr, b, arg_arr))
		return ;
	else if ((*tok_ptr) && (*tok_ptr)->type != '|')
		*tok_ptr = (*tok_ptr)->next;
}
