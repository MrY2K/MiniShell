/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:09 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/05 12:33:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_1(char *s1, char *s2)
{
	char	*str_final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	if (!s2 || !s1)
		return (NULL);
	str_final = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (str_final == NULL)
		return (NULL);
	while (s1[j])
		str_final[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_final[i++] = s2[j++];
	str_final[i] = '\0';
	return (str_final);
}

void	free_ft_split(char **list)
{
	int	i;

	if (list == NULL)
		return ;
	i = 0;
	while (list[i] != NULL)
	{
		free(list[i]);
		i++;
	}
	free(list);
	list = NULL;
}

char	*ft_path_cmd(char **list, char *ptr, char *tmp)
{
	char	*tmp2;
	int		i;

	i = 0;
	while (list[i])
	{
		if (ptr[0] == '/')
			tmp2 = ft_strdup(ptr);
		else
		{
			tmp = ft_join(list[i], "/");
			tmp2 = ft_join(tmp, ptr);
			free(tmp);
		}
		if (access(tmp2, F_OK) != -1 || access(tmp2, X_OK) != -1)
		{
			free_ft_split(list);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	if (list != NULL)
		free_ft_split(list);
	return (ptr);
}

char	*path_command(char *ptr, char **env)
{
	t_path_cmd	path_cmd;

	path_cmd.tmp = NULL;
	if (ptr != NULL && ptr[0] == '\0')
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	if (ptr == NULL)
		return (NULL);
	if (ptr[0] == '.')
		return (ptr);
	path_cmd.path = ft_getenv("PATH", env);
	if (path_cmd.path == NULL)
		path_cmd.path = getcwd(NULL, 0);
	if (!path_cmd.path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_exit_status = 127;
		exit(EXIT_FAILURE);
	}
	path_cmd.list = ft_split(path_cmd.path, ':');
	return (ft_path_cmd(path_cmd.list, ptr, path_cmd.tmp));
}

void	ft_error(char *str, char *ptr)
{
	(void)str;
	ft_putstr_fd(ptr, 2);
	ft_putstr_fd(" not a valid identifier\n", 2);
	g_exit_status = 1;
}
