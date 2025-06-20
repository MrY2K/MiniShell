#include "../../includes/minishell.h"

void	ft_add_redir(t_redirect **lst, t_redirect *_new)
{
	t_redirect	*last;

	if (!lst || !_new)
		return ;
	if (*lst == NULL)
		*lst = _new;
	else
	{
		last = ft_last_redir(*lst);
		last->next = _new;
	}
}
t_redirect	*ft_last_redir(t_redirect *lst)
{
	t_redirect	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_redirect	*ft_new_redir(void *content, t_token_type type, int is_ambig)
{
	t_redirect	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_redirect));
	if (!new_node)
		return (NULL);
	new_node->file_path = content;
	new_node->type = type;
	new_node->is_ambig = is_ambig;
	new_node->next = NULL;
	return (new_node);
}

void	ft_next(t_token **tok_ptr, t_cmd **cmd_ptr)
{
	if ((*tok_ptr) != NULL && (*tok_ptr)->type == '|')
		(*tok_ptr) = (*tok_ptr)->next;
	if ((*cmd_ptr) != NULL)
		(*cmd_ptr) = (*cmd_ptr)->next;
	if ((*cmd_ptr) != NULL && (*tok_ptr) != NULL)
		(*cmd_ptr) = (*cmd_ptr)->next;
}

void	add_back_node_her(t_heredoc **her, t_heredoc *new_her)
{
	t_heredoc	*p;

	p = *her;
	if (!her || !new_her)
		return ;
	if (!(*her))
	{
		*her = new_her;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new_her;
}