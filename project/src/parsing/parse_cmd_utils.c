/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:14:28 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/21 02:14:55 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		redirection(t_token *start);
int		ft_len_arg(char **arg);
int		ft_search(char *s, char *d);

int	redirection(t_token *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == TOKEN_REDIR_APPEND
		|| (start)->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	ft_len_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == NULL)
		return (0);
	while (arg[i] != NULL)
	{
		i++;
	}
	return (i);
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

void	skip_whitespace(t_token **tok_ptr)
{
	while ((*tok_ptr) && (*tok_ptr)->type == ' ')
		*tok_ptr = (*tok_ptr)->next;
}

int	is_quote(t_token *head)
{
	if ((head)->type == '\"' || (head)->type == '\'')
		return (1);
	return (0);
}
