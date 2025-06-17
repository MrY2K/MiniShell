/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:10:59 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 23:09:38 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lookup_env_var(t_env **env, char *arg, char **str, int *i)
{
	t_env	*_env;

	_env = *env;
	while (_env)
	{
		if (search(_env->name, arg + (*i)))
		{
			*str = ft_strdup(_env->value);
			break ;
		}
		else
			*str = NULL;
		_env = _env->next;
	}
}

void	append_regular_characters(t_expand_heredoc *ex, char *line)
{
	ex->j = ex->index;
	while (line[ex->index] && line[ex->index] != '$')
	{
		ex->index++;
		ex->len++;
	}
	ex->s = ft_substr(line, ex->j, ex->len);
	ex->expanded_line = ft_strjoin(ex->expanded_line, ex->s);
	free (ex->s);
	ex->index--;
}

char	*expand_env_var_her(t_minibash *bash, t_env *env, char	**expanded_line, int *index, char *line)
{
	t_env_var	var;

	var.len = 0;
	(*index)++;
	var.j = *index;
	if (line[*index] == '?')
	{
		var.len++;
		(*index)++;
	}
	else
	{
		while (line[*index] && (ft_isalnum(line[*index])))
		{
			(*index)++;
			var.len++;
		}
	}
	(*index)--;
	var.j--;
	var.sub = ft_substr(line, var.j, ++var.len);
	var.str = expand(bash, &env, var.sub);
	*expanded_line = ft_strjoin(*expanded_line, var.str);
	free(var.sub);
	return (free (var.str), *expanded_line);
}

char	*expand_env_var_in_heredoc(t_minibash *bash, char *line, t_env *env)
{
	t_expand_heredoc	ex;

	ex.index = 0;
	while (line[ex.index])
	{
		ex.len = 0;
		if (line[ex.index] == '$')
			ex.expanded_line = expand_env_var_her(bash, env,
					&ex.expanded_line, &ex.index, line);
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
	if (heredoc->expand)
	{
		expanded_line = expand_env_var_in_heredoc(bash, line, tmp_env);
		ft_putendl_fd(expanded_line, fd);
		free (expanded_line);
	}
	else
		ft_putendl_fd(line, fd);
	free (path);
	close(fd);
}
