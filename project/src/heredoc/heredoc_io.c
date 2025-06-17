/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:10:59 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/17 12:39:52 by ajelloul         ###   ########.fr       */
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
	ex->str = ft_substr(line, ex->j, ex->len);
	ex->expanded_line = ft_strjoin(ex->expanded_line, ex->str);
	free (ex->str);
	ex->index--;
}

char	*expand_env_var_her(t_expand_info *info)
{
	t_env_var	var;

	var.len = 0;
	(*info->index)++;
	var.j = *info->index;
	if (info->line[*info->index] == '?')
	{
		var.len++;
		(*info->index)++;
	}
	else
	{
		while (info->line[*info->index] && ft_isalnum(info->line[*info->index]))
		{
			(*info->index)++;
			var.len++;
		}
	}
	(*info->index)--;
	var.j--;
	var.sub = ft_substr(info->line, var.j, ++var.len);
	var.str = expand(info->bash, &info->env, var.sub);
	*info->expanded_line = ft_strjoin(*info->expanded_line, var.str);
	free(var.sub);
	return (free(var.str), *info->expanded_line);
}

char	*expand_env_var_in_heredoc(t_minibash *bash, char *line, t_env *env)
{
	t_expand_heredoc	ex;
	t_expand_info		info;

	ex.index = 0;
	info.bash = bash;
	info.env = env;
	info.expanded_line = &ex.expanded_line;
	info.index = &ex.index;
	info.line = line;
	while (line[ex.index])
	{
		ex.len = 0;
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
