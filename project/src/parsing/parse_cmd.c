/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:15:01 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 04:17:00 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_input_commands(t_token **token_list, t_cmd **cmd_list,
		t_env *env, t_minibash *b)
{
	t_token	*cur_token;
	t_cmd	**tmp_cmd;

	tmp_cmd = cmd_list;
	cur_token = *token_list;
	while (cur_token != NULL)
	{
		append_command(tmp_cmd, create_new_command(&cur_token, env, b));
	}
	process_redirections(tmp_cmd, token_list, env, b);
}

void	append_command(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (!cmd_list || !new_cmd)
		return ;
	if (!*cmd_list)
		*cmd_list = new_cmd;
	else
	{
		last = last_command(*cmd_list);
		last->next = new_cmd;
	}
}

t_cmd	*last_command(t_cmd *cmd_list)
{
	t_cmd	*last;

	last = cmd_list;
	if (!cmd_list)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_cmd	*create_new_command(t_token **tok_ptr, t_env *env, t_minibash *b)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->argument = NULL;
	node->main_cmd = NULL;
	node->arg_len = 0;
	node->pipe = 0;
	node->red = NULL;
	node->heredoc = NULL;
	node->env_arr = NULL;
	if ((*tok_ptr) != NULL && ((*tok_ptr)->type == '|'
			&& (*tok_ptr)->state == N))
	{
		join_to_arg_array(&(node->argument), (*tok_ptr)->value);
		node->pipe = 1;
		*tok_ptr = (*tok_ptr)->next;
	}
	else if ((*tok_ptr) != NULL)
		process_non_pipe_segment(&node, tok_ptr, env, b);
	if (node->argument && node->argument[0])
		node->main_cmd = node->argument[0];
	node->next = NULL;
	return (node);
}

/*
* Append the token string to the command's argument array.
*/
void	join_to_arg_array(char ***arg_arr, char *tok_str)
{
	int		current_len;
	char	*dup;

	current_len = ft_len_arg(*arg_arr);
	if (!tok_str)
		return ;
	if (current_len == 0)
	{
		*arg_arr = NULL;
		*arg_arr = malloc(2 * sizeof(char *));
		(*arg_arr)[0] = ft_strdup(tok_str);
		(*arg_arr)[1] = NULL;
	}
	else
	{
		dup = ft_strdup(tok_str);
		current_len--;
		(*arg_arr)[current_len] = ft_strjoin((*arg_arr)[current_len], dup);
		free(dup);
	}
}
