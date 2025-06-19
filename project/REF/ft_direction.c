
#include "minishell.h"

void	ft_next(t_splitor **tmp_x, t_command **tmp_cmd)
{
	if ((*tmp_x) != NULL && (*tmp_x)->type == '|')
		(*tmp_x) = (*tmp_x)->next;
	if ((*tmp_cmd) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
	if ((*tmp_cmd) != NULL && (*tmp_x) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
}

char	*ft_fill_final(char **s)
{
	int		i;
	char	*final;

	final = NULL;
	i = 0;
	while (s[i] != NULL)
	{
		final = ft_strjoin(final, s[i]);
		if (s[i + 1] != NULL)
			final = ft_strjoin(final, " ");
		i++;
	}
	return (final);
}

int	ft_check_ambiguous(t_splitor *tmp_x, t_environment *my_env)
{
	char	*s;
	char	**str;

	s = NULL;
	while ((tmp_x) != NULL)
	{
		if ((tmp_x)->state == G && (redirection(tmp_x) || tmp_x->type == '|'
				|| tmp_x->type == ' '))
			break ;
		if ((tmp_x) != NULL && tmp_x->type == '$' && tmp_x->state == G)
		{
			s = ft_expand(tmp_x->in, &my_env);
			if (s == NULL || (s != NULL && (s[0] == ' ' || s[0] == '\0')))
				return (free(s), 1);
			str = ft_split(s, ' ');
			if (ft_len_arg(str) > 1)
				return (free(s), ft_free_argment(str), 1);
			free(s);
			ft_free_argment(str);
		}
		if ((tmp_x) != NULL)
			tmp_x = tmp_x->next;
	}
	return (0);
}

int	ft_check_quote(t_splitor **tmp_x, char **final)
{
	while (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL
			&& (redirection((*tmp_x)->next->next) != 1
				&& (*tmp_x)->next->next->type != 32
				&& (*tmp_x)->next->next->type == '$')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		return (1);
	}
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\'')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		*final = ft_strdup("");
		return (1);
	}
	return (0);
}


char	*ft_skip_direction(t_splitor **tmp_x, t_environment *my_env,
		int *is_amb, int her)
{
	t_dir	id;

	id.str = NULL;
	id.final = NULL;
	if (ft_check_quote(tmp_x, &id.final))
		;
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		*is_amb = ft_check_ambiguous((*tmp_x), my_env);
		if (*is_amb == 1 && her == 1)
			return (NULL);
		ft_double_and_sigle(tmp_x, my_env, her, &id.str);
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G)
	{
		*is_amb = ft_check_ambiguous((*tmp_x), my_env);
		if (*is_amb == 1 && her == 1)
			return (NULL);
		ft_word(tmp_x, my_env, her, &id.str);
	}
	if (id.str != NULL)
		id.final = ft_fill_final(id.str);
	return (free_args(id.str), id.final);
}


void	ft_fill_redirection(t_pre *id, t_environment *my_env, char *final)
{
	if (id->tmp_x != NULL && id->tmp_x->type == '>' && id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '>', id->is_amb));
	}
	else if (id->tmp_x != NULL && id->tmp_x->type == '<'
		&& id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, '<', id->is_amb));
	}
	else if (id->tmp_x != NULL && id->tmp_x->type == DREDIR_OUT
		&& id->tmp_x->state == G)
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 1);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, DREDIR_OUT,
				id->is_amb));
	}
}

void	ft_fill_her(t_pre *id, t_environment *my_env, char *final)
{
	while ((id->tmp_x != NULL && id->tmp_x->type == HERE_DOC
			&& id->tmp_x->state == G))
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		if ((id->tmp_x != NULL && id->tmp_x->state == G)
			&& ((id->tmp_x->next != NULL && id->tmp_x->next->type == ' ')
				|| (id->tmp_x->next == NULL)))
			id->is_expand = 1;
		final = ft_skip_direction(&id->tmp_x, my_env, &id->is_amb, 0);
		add_back_node_her(&(id->tmp_cmd->her), new_node_her(final, -1, id->j,
				id->is_expand));
		id->j++;
	}
}

void	ft_check_redirection(t_pre *id, t_environment *my_env)
{
	char	*final;

	final = NULL;
	while ((id->tmp_x) != NULL && (redirection(id->tmp_x)
			&& id->tmp_x->state == G))
	{
		if (id->tmp_x != NULL && (redirection(id->tmp_x)
				&& id->tmp_x->type != HERE_DOC))
			ft_fill_redirection(id, my_env, final);
		else if ((id->tmp_x != NULL && id->tmp_x->type == HERE_DOC
				&& id->tmp_x->state == G))
			ft_fill_her(id, my_env, final);
	}
	if (id->tmp_x != NULL && !(id->tmp_x->type == '|' && id->tmp_x->state == G))
		id->tmp_x = id->tmp_x->next;
}

void	ft_fill_red(t_command **cmd, t_splitor **x, t_environment *my_env)
{
	t_pre	id;

	if (cmd == NULL || x == NULL)
		return ;
	id.is_expand = 0;
	id.is_amb = 0;
	id.j = 0;
	id.i = 0;
	id.tmp_cmd = *cmd;
	id.tmp_x = *x;
	while (id.tmp_cmd != NULL && id.tmp_x != NULL)
	{
		id.tmp_cmd->doc = NULL;
		id.i = 0;
		while ((id.tmp_cmd != NULL && id.tmp_x != NULL)
			&& !(id.tmp_x->state == G && id.tmp_x->type == '|'))
		{
			ft_check_redirection(&id, my_env);
			id.i++;
		}
		ft_next(&id.tmp_x, &id.tmp_cmd);
	}
}

t_redirect	*ft_new_redir(void *content, t_token type, int is_amb)
{
	t_redirect	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_redirect));
	if (!new_node)
		return (NULL);
	new_node->store = content;
	new_node->type = type;
	new_node->is_amb = is_amb;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_redir(t_redirect **lst, t_redirect *new)
{
	t_redirect	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_redir(*lst);
		last->next = new;
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

t_here_doc	*new_node_her(char *file, int fd, int x, int is_expand)
{
	t_here_doc	*elem;
	char		*tmp_line;
	char		*path_file;
	char		*it;

	it = ft_itoa(x);
	elem = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!elem)
		return (NULL);
	tmp_line = ft_strjoin_1(file, it);
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(it);
	elem->store = file;
	elem->fd = fd;
	elem->idx = x;
	elem->expad = is_expand;
	elem->heredoc_file = (path_file);
	elem->next = NULL;
	return (elem);
}

void	add_back_node_her(t_here_doc **her, t_here_doc *new_her)
{
	t_here_doc	*p;

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
