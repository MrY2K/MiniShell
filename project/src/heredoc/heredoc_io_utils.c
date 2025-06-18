/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_io_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:46:06 by ajelloul          #+#    #+#             */
/*   Updated: 2025/06/18 09:40:56 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_heredoc_file_name(t_heredoc *her)
{
	char	*index;
	char	*join_del;
	char	*path;

	index = ft_itoa(her->index);
	join_del = ft_strjoin_with_null(her->delimiter, index);
	path = ft_strjoin_with_null("/tmp/minishell/heredoc", join_del);
	free (index);
	free (join_del);
	return (path);
}

t_cmd	*get_last_heredoc(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp->heredoc->next)
		tmp->heredoc = tmp->heredoc->next;
	return (tmp);
}

int	open_heredoc_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_putendl_fd("minishell: No such file or directory", 2);
		return (-1);
	}
	return (fd);
}

int	setup_heredoc_input(int fd)
{
	if (dup2(fd, 0) < 0)
	{
		perror("dup2");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}
