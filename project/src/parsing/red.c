/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:16:16 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:19:46 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_handle_redirection(t_expand_heredoc *id, t_env *env,
	char *final, t_minibash *b)
{
	if (id->tmp_t != NULL && id->tmp_t->type == '>' && id->tmp_t->state == N)
	{
		id->tmp_t = id->tmp_t->next;
		ft_skip_spaces(&id->tmp_t);
		final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1, b);
		ft_add_red(&(id->tmp_cmd->red), ft_new_redir(final, '>', id->is_ambig));
	}
	else if (id->tmp_t != NULL && id->tmp_t->type == '<'
		&& id->tmp_t->state == N)
	{
		id->tmp_t = id->tmp_t->next;
		ft_skip_spaces(&id->tmp_t);
		final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1, b);
		ft_add_red(&(id->tmp_cmd->red), ft_new_redir(final, '<', id->is_ambig));
	}
	else if (id->tmp_t != NULL && id->tmp_t->type == TOKEN_REDIR_APPEND
		&& id->tmp_t->state == N)
	{
		id->tmp_t = id->tmp_t->next;
		ft_skip_spaces(&id->tmp_t);
		final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1, b);
		ft_add_red(&(id->tmp_cmd->red), ft_new_redir(final, TOKEN_REDIR_APPEND,
				id->is_ambig));
	}
}

char	*ft_skip_direction(t_token **tmp_t, t_env *env,
		int *is_ambig, int her, t_minibash *b)
{
	t_dir	id;

	id.str = NULL;
	id.final = NULL;
	if (ft_check_quote(tmp_t, &id.final))
		;
	else if ((*tmp_t) != NULL && (*tmp_t)->state == N
		&& ((*tmp_t)->type == '\"' || (*tmp_t)->type == '\''))
	{
		*is_ambig = ft_check_ambiguous((*tmp_t), env, *b);
		if (*is_ambig == 1 && her == 1)
			return (NULL);
		process_quoted(tmp_t, env, her, &id.str);
	}
	else if ((*tmp_t) != NULL && (*tmp_t)->state == N)
	{
		*is_ambig = ft_check_ambiguous((*tmp_t), env, *b);
		if (*is_ambig == 1 && her == 1)
			return (NULL);
		process_word(tmp_t, env, her, &id.str);
	}
	if (id.str != NULL)
		id.final = ft_fill_final(id.str);
	return (free_argument_array(id.str), id.final);
}

void	ft_handle_her(t_expand_heredoc *id, t_env *env,
		char *final, t_minibash *b)
{
	while ((id->tmp_t != NULL && id->tmp_t->type == TOKEN_HEREDOC
			&& id->tmp_t->state == N))
	{
		id->tmp_t = id->tmp_t->next;
		ft_skip_spaces(&id->tmp_t);
		if ((id->tmp_t != NULL && id->tmp_t->state == N)
			&& ((id->tmp_t->next != NULL && id->tmp_t->next->type == ' ')
				|| (id->tmp_t->next == NULL)))
			id->is_expand = 1;
		final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 0, b);
		add_back_node_her(&(id->tmp_cmd->heredoc),
			new_node_her(final, -1, id->j, id->is_expand));
		id->j++;
	}
}

void	ft_handler_red_her(t_expand_heredoc *id, t_env *env, t_minibash *b)
{
	char	*final;

	final = NULL;
	while ((id->tmp_t) != NULL && (redirection(id->tmp_t)
			&& id->tmp_t->state == N))
	{
		if (id->tmp_t != NULL && (redirection(id->tmp_t)
				&& id->tmp_t->type != TOKEN_HEREDOC))
			ft_handle_redirection(id, env, final, b);
		else if ((id->tmp_t != NULL && id->tmp_t->type == TOKEN_HEREDOC
				&& id->tmp_t->state == N))
			ft_handle_her(id, env, final, b);
	}
	if (id->tmp_t != NULL && !(id->tmp_t->type == '|'
			&& id->tmp_t->state == N))
		id->tmp_t = id->tmp_t->next;
}

void	process_redirections(t_cmd **cmd, t_token **tokens,
		t_env *env, t_minibash *b)
{
	t_expand_heredoc	id;

	if (cmd == NULL || tokens == NULL)
		return ;
	id.is_expand = 0;
	id.is_ambig = 0;
	id.j = 0;
	id.i = 0;
	id.tmp_cmd = *cmd;
	id.tmp_t = *tokens;
	while (id.tmp_cmd != NULL && id.tmp_t != NULL)
	{
		id.tmp_cmd->red = NULL;
		id.i = 0;
		while ((id.tmp_cmd != NULL && id.tmp_t != NULL)
			&& !(id.tmp_t->state == N && id.tmp_t->type == '|'))
		{
			ft_handler_red_her(&id, env, b);
			id.i++;
		}
		ft_next(&id.tmp_t, &id.tmp_cmd);
	}
}
