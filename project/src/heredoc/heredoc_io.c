/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:10:59 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/20 16:22:59 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	lookup_env_var(t_env **env, char *arg, char **str, int *i)
{
	t_env	*_env;
	char	*var_name;
	int		len;

	*str = NULL;
	_env = *env;
	len = 0;
	while (arg[*i + len] && (ft_isalnum(arg[*i + len]) || arg[*i + len] == '_'))
		len++;
	if (len == 0)
		return ;
	var_name = ft_substr(arg, *i, len);
	if (!var_name)
		return ;
	while (_env)
	{
		if (ft_strcmp(_env->name, var_name) == 0)
		{
			*str = ft_strdup(_env->value);
			break ;
		}
		_env = _env->next;
	}
	if (!*str)
		*str = ft_strdup("");
	free(var_name);
}

char	*ft__expand(t_minibash *bash, t_env **env, char *str)
{
	t_expand_heredoc	ex;
	char				*result;

	if (!str || !*str)
		return (ft_strdup(""));
	ft_memset(&ex, 0, sizeof(ex));
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(bash->exit_status));
	if (search("$\"\"", str))
		return (ft_strdup(""));
	if (str[0] && !str[1])
	{
		if (str[0] == '"' || str[0] == '\'' || !ft_isalnum(str[0])
			|| ft_isdigit(str[0]))
			return (ft_strdup(""));
	}
	lookup_env_var(env, str, &result, &ex.index);
	return (result ? result : ft_strdup(""));
}

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

char	*expand_env_var_her(t_expand_info *info)
{
	t_env_var	var;
	char		*temp;

	var.len = 0;
	(*info->index)++;
	var.j = *info->index;
	if (info->line[*info->index] == '?')
	{
		var.str = ft_itoa(info->bash->exit_status);
		(*info->index)++;
	}
	else
	{
		while (info->line[*info->index] && (ft_isalnum(info->line[*info->index])
				|| info->line[*info->index] == '_'))
		{
			(*info->index)++;
			var.len++;
		}
		if (var.len == 0)
			var.str = ft_strdup("$");
		else
		{
			var.sub = ft_substr(info->line, var.j, var.len);
			var.str = ft__expand(info->bash, &info->env, var.sub);
			free(var.sub);
		}
	}
	if (!*info->expanded_line)
		*info->expanded_line = ft_strdup("");
	temp = *info->expanded_line;
	*info->expanded_line = ft_strjoin(temp, var.str ? var.str : "");
	free(temp);
	free(var.str);
	(*info->index)--;
	return (*info->expanded_line);
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
	if (heredoc->expand == 1)
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
