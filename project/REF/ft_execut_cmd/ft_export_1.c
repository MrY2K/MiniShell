/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:49:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/27 19:42:16 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum_exp(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || (c == '_') || c == '<' || c == '>');
}

void	print_export(t_environment **var)
{
	t_environment	*ptr;

	if (*var == NULL || var == NULL)
		return ;
	ptr = *var;
	while (ptr != NULL)
	{
		if (ptr->data == NULL)
			printf("declare -x %s\n", (char *)ptr->var);
		else if (ptr->data != NULL && ptr->data[0] == '='
			&& ptr->data[1] == '\0')
			printf("declare -x %s=\"\"\n", (char *)ptr->var);
		else
			printf("declare -x %s=\"%s\"\n", (char *)ptr->var,
				(char *)ptr->data);
		ptr = ptr->next;
	}
	return ;
}

int	exist_redir(char *ptr)
{
	if (!ptr)
		return (0);
	if (ft_strcmp(ptr, ">") == 0)
		return (1);
	if (ft_strcmp(ptr, ">>") == 0)
		return (1);
	if (ft_strcmp(ptr, "<") == 0)
		return (1);
	return (0);
}

char	*first_word(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	while (ptr[i] && ptr[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (ptr[i] && ptr[i] != '=')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
