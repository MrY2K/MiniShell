/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:10:59 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/27 18:47:41 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lookup_env_var(t_env **env, char *arg, char **str, int *i)
{
	t_env	*cur;
	char	*var_name;
	int		len;

	len = 0;
	cur = *env;
	while (arg[*i + len] && (ft_isalnum(arg[*i + len]) || arg[*i + len] == '_'))
		len++;
	if (len == 0)
		return ;
	var_name = ft_substr(arg, *i, len);
	if (!var_name)
		return ;
	while (cur)
	{
		if (ft_strcmp(cur->name, var_name) == 0)
		{
			*str = ft_strdup(cur->value);
			break ;
		}
		cur = cur->next;
	}
	if (!*str)
		*str = ft_strdup("");
	free(var_name);
}

/*
	This function appends all regular characters (before a '$')

	Input line:     "Hello $USER"  
	After call:      expanded_line = "Hello "

*/

void	append_regular_characters(t_expand_heredoc *ex, char *line)
{
	char	*temp;

	ex->j = ex->index;
	ex->len = 0;
	while (line[ex->index] && line[ex->index] != '$')
	{
		ex->index++;
		ex->len++;
	}
	if (ex->len > 0)
	{
		ex->s = ft_substr(line, ex->j, ex->len);
		if (ex->s)
		{
			if (!ex->expanded_line)
				ex->expanded_line = ft_strdup("");
			temp = ex->expanded_line;
			ex->expanded_line = ft_strjoin(temp, ex->s);
			free(temp);
			free(ex->s);
		}
	}
	ex->index--;
}

char	*expand_env_var_in_heredoc(t_minibash *bash, char *line, t_env *env)
{
	t_expand_heredoc	ex;
	t_expand_info		info;

	ft_memset(&ex, 0, sizeof(ex));
	ft_memset(&info, 0, sizeof(info));
	ex.expanded_line = ft_strdup("");
	info.bash = bash;
	info.env = env;
	info.expanded_line = &ex.expanded_line;
	info.index = &ex.index;
	info.line = line;
	while (line[ex.index])
	{
		if (line[ex.index] == '$')
			ex.expanded_line = expand_env_var_her(&info);
		else
			append_regular_characters(&ex, line);
		ex.index++;
	}
	return (ex.expanded_line);
}

void	write_in_heredoc_files(t_minibash *bash, t_env **env,
	t_heredoc *heredoc, char *line)
{
	t_env	*tmp_env;
	char	*path;
	char	*expanded_line;
	int		fd;

	expanded_line = NULL;
	tmp_env = *env;
	path = get_path(heredoc);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0)
	{
		free (path);
		return (perror("open"));
	}
	expanded_line = expand_env_var_in_heredoc(bash, line, tmp_env);
	ft_putendl_fd(expanded_line, fd);
	free (expanded_line);
	free (path);
	close(fd);
}
