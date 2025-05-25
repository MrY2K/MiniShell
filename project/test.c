


int	ft_check_input(char str_input)
{
	if (str_input == '|' || str_input == '<' || str_input == '>'
		|| str_input == '$' || str_input == '\'' || str_input == '\"'
		|| ft_isspace(str_input))
		return (1);
	return (0);
}



int	ft_isprint(int c)
{
	return (c == 9 || (c >= 32 && c <= 126));
}

void	ft_add(t_splitor **lst, t_splitor *new)
{
	t_splitor	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}


t_state	ft_get_state(t_idx *var, char s)
{
	if (var->in_d == -1 && s == '\"' && var->in_s == -1)
		return (var->in_d = 1, G); 
	else if (var->in_d == 1 && s == '\"' && var->in_s == -1)
		return (var->in_d = -1, G);
	else if (var->in_d == 1 && ft_isprint(s) && var->in_s == -1)
		return (D);
	else if (var->in_d == -1 && ft_isprint(s) && var->in_s == -1 && s != '\'')
		return (G);
	else if (var->in_s == -1 && s == '\'' && var->in_d == -1)
		return (var->in_s = 1, G);
	else if (var->in_s == 1 && s == '\'' && var->in_d == -1)
		return (var->in_s = -1, G);
	else if (var->in_s == 1 && ft_isprint(s) && var->in_d == -1)
		return (S);
	else if (var->in_s == -1 && ft_isprint(s) && var->in_d == -1 && s != '\"')
		return (G);
	return (3);
}

typedef struct s_splitor
{
	char				*in;
	int					len;
	enum e_token		type;
	int					is_amb;
	int					is_exp;
	enum e_state		state;
	struct s_splitor	*next;
	struct s_splitor	*prev;
}						t_splitor;

t_splitor	*ft_lstnew(void *content, int len, t_token type, t_state state)
{
	t_splitor	*new_node;

	new_node = malloc(sizeof(t_splitor));
	if (!new_node)
		return (NULL);
	new_node->in = content;
	new_node->len = len;
	new_node->type = type;
	new_node->state = state;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}


void	ft_get_word(char *s, t_idx *var, t_splitor **x)
{
	int	i;

	i = 0;
	while (s[var->i] && !ft_check_input(s[var->i]))
	{
		var->state = ft_get_state(var, s[var->i]);
		var->i++;
		var->len++; 
		i++;
	}
	ft_add(x, ft_lstnew(value, var->len, WORD,var->state));
}

void	ft_get_env(char *s, t_idx *var, t_splitor **x)
{
	if ((s[var->i] && s[var->i + 1] && s[var->i + 2] && s[var->i] == '$')
		&& ((s[var->i + 1] == '\"' && s[var->i + 2] == '\"') || (s[var->i
					+ 1] == '\'' && s[var->i + 2] == '\'')))
	{
		//It creates an ENV token (because it's in ft_get_env).
		var->state = G;
		var->i++;
		var->i++;
		var->i++;
		var->len++;
		var->len++;
		var->len++;
	}
	else if ((s[var->i] && s[var->i + 1] && s[var->i + 2] && s[var->i] == '$')
		&& ((s[var->i + 1] == '\"') || (s[var->i + 1] == '\'')) && (s[var->i
				+ 2] != '\'' || s[var->i + 2] != '\"'))
	{
		var->i++;
		var->state = ft_get_state(var, s[var->i]);
		var->len++;
	}
	else
		ft_check_env(s, var);
	ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len, ENV,
			var->state));
}

void	ft_her_dir(t_splitor **x, t_idx *var, char *s)
{
	var->len++;
	var->i++;
	if (var->len >= 1 && s[var->i] == '<')
		ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
				HERE_DOC, ft_get_state(var, s[var->i])));
	else if (var->len >= 1 && s[var->i] == '>')
		ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
				DREDIR_OUT, ft_get_state(var, s[var->i])));
}



void	ft_get_char(char *s, t_idx *var, t_splitor **x)
{
	var->len++;
	if (s[var->i] && s[var->i] == '$')
		ft_get_env(s, var, x);
	else
	{
		if (s[var->i] && ((s[var->i] == '>' && s[var->i + 1] == '>')
				|| (s[var->i] == '<' && s[var->i + 1] == '<')))
			ft_her_dir(x, var, s);
		else
			ft_add(x, ft_lstnew(ft_substr(s, var->start, var->len), var->len,
					ft_get_token(s[var->i]), ft_get_state(var, s[var->i])));
	}
	var->i++;
}


int	ft_lexer(char *s, t_splitor **x)
{
	t_idx	var;
	int		str_input_len;

	str_input_len = ft_strlen(s);
	var.i = 0;
	var.in_d = -1;
	var.in_s = -1;
	while (var.i < str_input_len)
	{
		var.start = var.i;
		var.len = 0;
		if (s[var.i] && !ft_check_input(s[var.i]))
			ft_get_word(s, &var, x);
		else if (s[var.i] && ft_check_input(s[var.i]))
			ft_get_char(s, &var, x);
	}
	if (var.in_d == 1 || var.in_s == 1 || ft_handler_syn_error(x))
		return (1);
	return (0);
}
