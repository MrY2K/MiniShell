/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/10/05 19:10:00 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_var(t_environment *var)
{
	t_environment	*tmp;
	int				size;

	if (var == NULL)
		return (0);
	tmp = var;
	size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	*return_arry_result(t_envar *arry, t_environment *tmp_cmd)
{
	char	*result;

	arry->var_1 = ft_strdup(tmp_cmd->var);
	arry->var_2 = ft_strdup(tmp_cmd->data);
	arry->res = ft_strjoin(arry->var_1, "=");
	if (arry->var_2 != NULL)
	{
		result = ft_strjoin(arry->res, arry->var_2);
		free(arry->var_2);
	}
	else
	{
		result = ft_strdup(arry->res);
		free(arry->res);
	}
	return (result);
}

char	**array_env(t_environment **var)
{
	t_envar			arry;
	t_environment	*tmp_cmd;
	int				i;

	tmp_cmd = *var;
	arry.len = len_var(*var);
	arry.env_v = (char **)malloc(sizeof(char *) * (arry.len + 1));
	if (arry.env_v == NULL)
		return (NULL);
	i = 0;
	while (i < arry.len)
	{
		arry.env_v[i] = return_arry_result(&arry, tmp_cmd);
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	arry.env_v[i] = NULL;
	return (arry.env_v);
}

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (0);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		ptr[i] = s2[j];
		j++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_check_built(t_command *list)
{
	t_command	*tmp;

	tmp = list;
	if (ft_strcmp(tmp->content, "export") == 0 && tmp->arg[1] != NULL)
		return (1);
	if (ft_strcmp(tmp->content, "unset") == 0 && tmp->arg[1] != NULL)
		return (1);
	if (ft_strcmp(tmp->content, "cd") == 0)
		return (1);
	if (ft_strcmp(tmp->content, "exit") == 0)
		return (1);
	return (0);
}
