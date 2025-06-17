#include "../../includes/minishell.h"

void	ft_skip_spaces(t_token **tok_ptr)
{
    while ((*tok_ptr) && (*tok_ptr)->type == ' ')
        *tok_ptr = (*tok_ptr)->next;
}


t_redirect	*ft_new_redir(char *file_path, int type, int is_ambig)
{
    t_redirect	*redir;

    redir = malloc(sizeof(t_redirect));
    if (!redir)
        return (NULL);
    redir->file_path = file_path;
    redir->type = type;
    redir->is_ambig = is_ambig;
    redir->next = NULL;
    return (redir);
}

void	ft_add_redir(t_redirect **redirections, t_redirect *new_redir)
{
    t_redirect	*last;

    if (!redirections || !new_redir)
        return ;
    if (!*redirections)
        *redirections = new_redir;
    else
    {
        last = *redirections;
        while (last->next)
            last = last->next;
        last->next = new_redir;
    }
}

void	ft_next(t_token **tok_ptr, t_cmd **cmd_ptr)
{
    if (*tok_ptr && (*tok_ptr)->type == '|')
    {
        *tok_ptr = (*tok_ptr)->next;
        if (*cmd_ptr)
            *cmd_ptr = (*cmd_ptr)->next;
    }
}

void	ft_check_redirection(t_expand_heredoc *id, t_env *env)
{
    char	*final;

    final = NULL;
    if (id->tmp_t != NULL && id->tmp_t->type == '>' && id->tmp_t->state == Normal)
    {
        id->tmp_t = id->tmp_t->next;
        ft_skip_spaces(&id->tmp_t);
        final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1);
        ft_add_redir(&(id->tmp_cmd->redirections), ft_new_redir(final, '>', id->is_ambig));
    }
    else if (id->tmp_t != NULL && id->tmp_t->type == '<' && id->tmp_t->state == Normal)
    {
        id->tmp_t = id->tmp_t->next;
        ft_skip_spaces(&id->tmp_t);
        final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1);
        ft_add_redir(&(id->tmp_cmd->redirections), ft_new_redir(final, '<', id->is_ambig));
    }
    else if (id->tmp_t != NULL && id->tmp_t->type == TOKEN_REDIR_APPEND && id->tmp_t->state == Normal)
    {
        id->tmp_t = id->tmp_t->next;
        ft_skip_spaces(&id->tmp_t);
        final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1);
        ft_add_redir(&(id->tmp_cmd->redirections), ft_new_redir(final, TOKEN_REDIR_APPEND, id->is_ambig));
    }
    else if (id->tmp_t != NULL && id->tmp_t->type == TOKEN_HEREDOC && id->tmp_t->state == Normal)
    {
        id->tmp_t = id->tmp_t->next;
        ft_skip_spaces(&id->tmp_t);
        final = ft_skip_direction(&id->tmp_t, env, &id->is_ambig, 1);
        ft_add_redir(&(id->tmp_cmd->redirections), ft_new_redir(final, TOKEN_HEREDOC, id->is_ambig));
    }
}

void	process_redirections(t_cmd **cmd, t_token **tokens, t_env *env)
{
    t_expand_heredoc	id;

	if (cmd == NULL || tokens == NULL)
		return ;
	id.is_expand = 0;
	id.is_ambig = 0;
	id.j = 0;
	id.index = 0;
	id.tmp_cmd = *cmd;
	id.tmp_t = *tokens;
	while (id.tmp_cmd != NULL && id.tmp_t != NULL)
	{
		id.tmp_cmd->redirections = NULL;
		id.index = 0;
		while ((id.tmp_cmd != NULL && id.tmp_t != NULL)
			&& !(id.tmp_t->state == Normal && id.tmp_t->type == '|'))
		{
			ft_check_redirection(&id, env);
			id.index++;
		}
		ft_next(&id.tmp_t, &id.tmp_cmd);
	}
}

