
int						g_exit_status;

typedef struct s_idx
{
	int					i;
	int					j;
	int					len;
	int					start;
	int					state;
	int					in_s;
	int					in_d;
}						t_idx;

typedef struct ft_cd
{
	char				*path;
	char				*ptr;
	char				**env;
}						t_cd;
typedef struct s_expand_her
{
	int					i;
	int					j;
	int					len;
	char				*final;
	char				*s;
}						t_expand_her;

typedef struct path_cmd
{
	char				*path;
	char				**list;
	char				*tmp;
}						t_path_cmd;

typedef enum e_token
{
	nothing = 0,
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}						t_token;

typedef struct s_redirect
{
	t_token				type;
	int					is_amb;
	char				*store;
	struct s_redirect	*next;
}						t_redirect;

typedef enum e_state
{
	D, 
	S,
	G,
	NUL,
}						t_state;
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

typedef struct s_envarment
{
	char				*var;
	char				*data;
	struct s_envarment	*next;
}						t_environment;

typedef struct s_here_doc
{
	char				*store;
	int					fd;
	char				*heredoc_file;
	int					idx;
	int					expad;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_command
{
	char				*content;
	char				**arg;
	t_redirect			*doc;
	t_here_doc			*her;
	char				**ar_env;
	int					is_amb;
	int					is_exp;
	int					is_pipe;
	int					len;
	struct s_command	*next;
}						t_command;

typedef struct s_array_env
{
	char				**env_v;
	int					len;
	char				*var_1;
	char				*var_2;
	char				*res;
}						t_envar;

typedef struct s_pre
{
	char				*final;
	int					i;
	int					j;
	int					is_expand;
	int					is_amb;
	t_command			*tmp_cmd;
	t_splitor			*tmp_x;
}						t_pre;

typedef struct s_pipe
{
	int					num_cmd;
	int					**pipefd;
	t_command			*tmp_cmd;
	int					*pids;
	int					heredoc_fd;
	int					i;
	char				*ptr;
	char				**arry;
}						t_pipe;

typedef struct s_ps
{
	int					len_of_arg;
	int					len_of_join;
	char				**new_arg;
	int					idx;
	int					j;
}						t_ps;

typedef struct delet_file
{
	t_command			*tmp;
	t_here_doc			*her;
	char				*ptr;
	char				*file;
	char				*itoa;
}						t_delet;

typedef struct check_var
{
	char				*ptr_1;
	char				*ptr_2;
	t_environment		*elem;
	char				**list;
}						t_check_var;

typedef struct s_dir
{
	char				*final;
	char				**str;
}						t_dir;
typedef struct had_var
{
	int					len;
	int					j;
	char				*s;
	char				*sub;

}						t_had_var;



void	parent_proc(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		g_exit_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}



int	chech_fork(int pid)
{
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

void	delet_files(t_command *cmd)
{
	t_delet	del;

	del.tmp = cmd;
	while (del.tmp != NULL)
	{
		del.her = del.tmp->her;
		while (del.her != NULL)
		{
			del.itoa = ft_itoa(del.her->idx);
			del.ptr = ft_strjoin_1(del.her->store, del.itoa);
			free(ft_itoa(del.her->idx));
			del.file = ft_join("/tmp/herdoc", del.ptr);
			free(del.ptr);
			if (unlink(del.file) != 0)
			{
				g_exit_status = 1;
				perror("");
			}
			free(del.file);
			del.her = del.her->next;
			free(del.itoa);
		}
		del.tmp = del.tmp->next;
	}
}

void	ft_built_in(t_environment **var, t_command *list)
{
	if (test_redir(list) == 1)
	{
		if (file_not_valid(list) == 1)
			return ;
	}
	if (list->arg[1] != NULL)
		built_in(var, list);
	if (ft_strcmp("cd", list->content) == 0 && list->arg[1] == NULL)
		built_in(var, list);
	if (ft_strcmp("exit", list->content) == 0 && list->arg[1] == NULL)
		built_in(var, list);
	return ;
}



void	built_in(t_environment **var, t_command *list)
{
	if (list == NULL)
		return ;
	if (ft_strcmp(list->content, "exit") == 0)
		(ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		(ft_cd(var, list));
	if (ft_strcmp(list->content, "pwd") == 0)
		(ft_pwd(list));
	if (ft_strcmp(list->content, "export") == 0)
	{
		(ft_export(var, list));
	}
	if (ft_strcmp(list->content, "unset") == 0)
		(ft_unset(var, list));
	if (ft_strcmp(list->content, "env") == 0)
		(ft_env(var));
	if (ft_strcmp(list->content, "echo") == 0)
	{
		(ft_echo(list));
	}
}


int	test_redir(t_command *list)
{
	t_redirect	*tmp;

	if (list == NULL)
		return (0);
	tmp = list->doc;
	while (tmp != NULL)
	{
		if (tmp->type == DREDIR_OUT || tmp->type == REDIR_OUT
			|| tmp->type == REDIR_IN)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp)
	{
		if (tmp->is_pipe == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}


int	built_in_exist(t_command *list)
{
	if (list == NULL)
		return (0);
	if (ft_strcmp(list->content, "exit") == 0)
		return (1);
	if (ft_strcmp(list->content, "cd") == 0)
		return (1);
	if (ft_strcmp(list->content, "pwd") == 0)
		return (1);
	if (ft_strcmp(list->content, "export") == 0)
		return (1);
	if (ft_strcmp(list->content, "unset") == 0)
		return (1);
	if (ft_strcmp(list->content, "env") == 0)
		return (1);
	if (ft_strcmp(list->content, "echo") == 0)
		return (1);
	return (0);
}

char	*ft_name_file(t_here_doc *tmp)
{
	char	*tmp_line;
	char	*path_file;
	char	*itoa;

	itoa = ft_itoa(tmp->idx);
	tmp_line = ft_strjoin_1(tmp->store, itoa);
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(itoa);
	return (path_file);
}

void	hundl_her_expand(t_expand_her *idx, char *line)
{
	idx->j = idx->i;
	while (line[idx->i] && line[idx->i] != '$')
	{
		idx->i++;
		idx->len++;
	}
	idx->s = ft_substr(line, idx->j, idx->len);
	idx->final = ft_strjoin(idx->final, idx->s);
	free(idx->s);
	idx->i--;
}



int	ft_search(char *s, char *d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] && s[i])
	{
		if (s[i] == d[j])
			j++;
		if (len == j && s[i + 1] == d[j])
			return (1);
		i++;
	}
	return (0);
}

void	ft_go_to_env(char **s, char *arg, int *i, t_environment **my_env)
{
	t_environment	*tmp_env;

	*s = NULL;
	tmp_env = *my_env;
	while (tmp_env != NULL)
	{
		if (ft_search(tmp_env->var, arg + (*i)))
		{
			*s = ft_strdup(tmp_env->data);
			break ;
		}
		else
			*s = NULL;
		tmp_env = tmp_env->next;
	}
}

char	*ft_expand(char *arg, t_environment **my_env)
{
	t_expand_her	id;

	id.i = 0;
	id.s = NULL;
	while (my_env != NULL && arg[id.i])
	{
		if (ft_search("$\"\"", arg))
			return (id.s = ft_strdup(""), id.s);
		else if (arg[id.i] == '$')
		{
			if (arg[id.i + 1] == '?')
				return (id.final = ft_itoa(g_exit_status),
					id.s = ft_strdup(id.final), free(id.final), id.s);
			id.i++;
			if (arg[id.i] == '\0')
				return (id.s = ft_strdup("$"), id.s);
			if (arg[id.i] == '\"' || arg[id.i] == '\'')
				return (id.s = ft_strdup(""), id.s);
			if (!ft_isalnum(arg[id.i]) || ft_isdigit(arg[id.i]))
				return (id.s);
			ft_go_to_env(&id.s, arg, &id.i, my_env);
		}
		id.i++;
	}
	return (id.s);
}

char	*ft_handle_var(char *line, int *i, t_environment *my_env, char **final)
{
	t_had_var	hand;

	hand.len = 0;
	(*i)++;
	hand.j = *i;
	if (line[*i] == '?')
	{
		(*i)++;
		hand.len++;
	}
	else
	{
		while (line[*i] && (ft_isalnum(line[*i])))
		{
			(*i)++;
			hand.len++;
		}
	}
	(*i)--;
	hand.j--;
	hand.sub = ft_substr(line, hand.j, ++hand.len);
	hand.s = ft_expand(hand.sub, &my_env);
	*final = ft_strjoin(*final, hand.s);
	free(hand.sub);
	return (free(hand.s), *final);
}

char	*ft_expand_in_her(char *line, t_environment *my_env)
{
	t_expand_her	idx;

	idx.s = NULL;
	idx.i = 0;
	idx.final = NULL;
	while (line[idx.i])
	{
		idx.len = 0;
		if (line[idx.i] == '$')
			idx.final = ft_handle_var(line, &idx.i, my_env, &idx.final);
		else
			hundl_her_expand(&idx, line);
		idx.i++;
	}
	return (idx.final);
}


void	write_in_file(t_here_doc *tmp, char *line, t_environment **var)
{
	t_environment	*my_env;
	char			*path_file;
	char			*final;

	my_env = *var;
	final = NULL;
	path_file = ft_name_file(tmp);
	tmp->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		perror("open");
		return ;
	}
	if (tmp->expad == 1)
	{
		final = ft_expand_in_her(line, my_env);
		ft_putstr_fd(final, tmp->fd);
		free(final);
	}
	else
		ft_putstr_fd(line, tmp->fd);
	free(path_file);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
}

void	hundle_chil_pro(t_here_doc *tmp_her, t_environment **var)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			g_exit_status = 0;
			exit(EXIT_SUCCESS);
		}
		if (ft_strcmp(line, tmp_her->store) == 0)
		{
			free(line);
			g_exit_status = 0;
			exit(EXIT_SUCCESS);
		}
		else
			write_in_file(tmp_her, line, var);
		free(line);
	}
}
int	handle_fork(t_here_doc *tmp_her, t_environment **var)
{
	int	pid;
	int	status;

	status = -1;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
		return (0);
	}
	if (pid == 0)
		hundle_chil_pro(tmp_her, var);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			g_exit_status = status;
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
	signal(SIGINT, hhandle_sig);
	return (status);
}


int	ft_cmp_delimeter(t_command *tmp_cmd, t_environment **var)
{
	t_here_doc	*tmp_her;
	int			status;

	status = -1;
	tmp_her = tmp_cmd->her;
	while (tmp_cmd != NULL && tmp_her != NULL)
	{
		status = handle_fork(tmp_her, var);
		if (WTERMSIG(status) == SIGINT)
		{
			return (status);
		}
		tmp_her = tmp_her->next;
	}
	return (status);
}

void	create_files(t_command *cmd, char *itoa)
{
	t_command	*tmp;
	t_here_doc	*tmp_her;
	char		*tmp_line;
	char		*path_file;

	if (cmd == NULL)
		return ;
	tmp = cmd;
	while (tmp != NULL)
	{
		tmp_her = tmp->her;
		while (tmp != NULL && tmp_her != NULL)
		{
			itoa = ft_itoa(tmp_her->idx);
			tmp_line = ft_strjoin_1(tmp_her->store, itoa);
			free(itoa);
			path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
			free(tmp_line);
			tmp_her->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
			free(path_file);
			close(tmp_her->fd);
			tmp_her = tmp_her->next;
		}
		tmp = tmp->next;
	}
}



bool	handle_here_doc(t_environment **var, t_command *cmd)
{
	t_command	*tmp_cmd;
	int			status;
	char		*itoa;
	bool		flag;

	itoa = NULL;
	flag = false;
	tmp_cmd = cmd;
	if (cmd == NULL || tmp_cmd == NULL)
		return (-1);
	create_files(tmp_cmd, itoa);
	while (tmp_cmd != NULL)
	{
		status = ft_cmp_delimeter(tmp_cmd, var);
		if (WTERMSIG(status) == SIGINT)
		{
			flag = true;
			break ;
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (flag);
}



int	count_herdoc(t_command *tmp)
{
	int			count;
	t_command	*cmd;
	t_here_doc	*her;

	cmd = tmp;
	count = 0;
	if (tmp == NULL)
		return (0);
	while (cmd != NULL)
	{
		her = cmd->her;
		if (her != NULL)
		{
			while (her != NULL)
			{
				if (her->store != NULL)
					count++;
				her = her->next;
			}
			cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
	return (count);
}


int	herdoc_exist(t_command *list)
{
	t_command	*tmp;
	int			count;

	if (list == NULL)
		return (0);
	count = 0;
	tmp = list;
	count = count_herdoc(tmp);
	if (count != 0)
		return (1);
	else
		return (0);
}


int	run_herdoc_built(t_environment **var, t_command *cmd)
{
	t_command	*list;

	list = cmd;
	if (list == NULL)
		return (0);
	if (herdoc_exist(list) == 1)
	{
		if (handle_here_doc(var, list) == true)
			return (-1);
		if (built_in_exist(list) == 1 && !pipe_exist(list) && !test_redir(list))
		{
			built_in(var, list);
			return (1);
		}
	}
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& herdoc_exist(list) == 0 && test_redir(list) == 0)
	{
		built_in(var, list);
		return (1);
	}
	else if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& ft_check_built(list) == 1)
		ft_built_in(var, list);
	return (0);
}

bool	execut_her_built(t_environment **var, t_command *cmd)
{
	t_command	*list;
	int			her;

	list = cmd;
	her = run_herdoc_built(var, cmd);
	if (her == -1)
	{
		delet_files(list);
		g_exit_status = 1;
		return (true);
	}
	if (her == 1)
	{
		delet_files(list);
		return (true);
	}
	return (false);
}


void	ft_exute(t_environment **var, t_command *cmd)
{
	t_command	*list;
	int			pid;

	list = cmd;
	if (execut_her_built(var, list) == true)
		return ;
	pid = fork();
	if (chech_fork(pid) == 1)
		return ;
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGQUIT, handl_sig_exec);
		signal(SIGINT, SIG_DFL);
		run_command(list, var);
	}
	else
	{
		parent_proc(pid);
		signal(SIGINT, hhandle_sig);
	}
	delet_files(cmd);
}

