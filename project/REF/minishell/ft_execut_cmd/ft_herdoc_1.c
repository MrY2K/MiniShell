/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:04:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/29 10:52:47 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
