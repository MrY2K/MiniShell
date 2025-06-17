#include "../../includes/minishell.h"
#include "../../includes/structs.h"


static int ft_search(const char *s, const char *d);
static void ft_go_to_env(char **out, char *arg, int *idx, t_env **env);
char *ft_expand(char *arg, t_env **env, t_minibash b);
int	ft_len_arg(char **arg);
void	ft_join_arr(char ***arr_join, char *in, t_minibash b);


/*
 * Pull in quoted text (single or double) and any embedded $-expansions,
 * joining everything into the same argument slot.
 */
void process_quoted(t_token **tok_ptr, t_env *env, int flag,
                    char ***arg_arr, t_minibash b)
{
    char *s;

    s = NULL;
    // While we have a quote token
    while (*tok_ptr
        && ((*tok_ptr)->type == '"' || (*tok_ptr)->type == '\'')
        && (*tok_ptr)->state == Normal)
    {
        // skip opening quote
        *tok_ptr = (*tok_ptr)->next;

        // 1) Handle any $-expansions inside quotes
        while (*tok_ptr
            && ((*tok_ptr)->state == Double || (*tok_ptr)->state == Single))
        {
            if ((*tok_ptr)->type == '$' && (*tok_ptr)->state == Double && flag)
            {
                s = ft_expand((*tok_ptr)->value, &env, b);
                ft_join_arr(arg_arr, s, b);
                free(s);
            }
            else
            {
                // literal text inside quotes
                ft_join_arr(arg_arr, (*tok_ptr)->value, b);
            }
            *tok_ptr = (*tok_ptr)->next;
        }

        // skip closing quote
        if (*tok_ptr && ((*tok_ptr)->type == '"' || (*tok_ptr)->type == '\''))
            *tok_ptr = (*tok_ptr)->next;
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// helper: check if string d is in s
static int ft_search(const char *s, const char *d)
{
    int i = 0, j = 0;
    int len = ft_strlen(s);
    while (s[i])
    {
        if (s[i] == d[j])
            j++;
        if (j == len && s[i + 1] == d[j])
            return 1;
        i++;
    }
    return 0;
}

// helper: retrieve env var value, scanning arg from index *idx
static void ft_go_to_env(char **out, char *arg, int *idx, t_env **env)
{
    t_env *tmp = *env;
    *out = NULL;
    while (tmp)
    {
        if (ft_search(tmp->name, arg + *idx))
        {
            *out = ft_strdup(tmp->value);
            break;
        }
        tmp = tmp->next;
    }
}

// Expand environment variables in arg; supports $?, $VAR, empty cases
char *ft_expand(char *arg, t_env **env, t_minibash b)
{
    t_expand_heredoc id;

    id.index = 0;
    id.str = NULL;
    while (env && arg[id.index])
    {
        if (ft_search("$\"\"", arg))
            return (id.str = ft_strdup(""), id.str);
        if (arg[id.index] == '$')
        {
            if (arg[id.index + 1] == '?')
                return (id.expanded_line = ft_itoa(b.exit_status), id.str = ft_strdup(id.expanded_line), free(id.expanded_line), id.str);
            id.index++;
            if (arg[id.index] == '\0')
                return (id.str = ft_strdup("$"), id.str);
            if (arg[id.index] == '"' || arg[id.index] == '\'')
                return (id.str = ft_strdup(""), id.str);
            if (!ft_isalnum(arg[id.index]))
                return id.str;
            ft_go_to_env(&id.str, arg, &id.index, env);
        }
        id.index++;
    }
    return id.str;
}

void	ft_join_arr(char ***arr_join, char *in, t_minibash b)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (in == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(in);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(in);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
}

int	redirection(t_token *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == TOKEN_REDIR_APPEND || (start)->type == TOKEN_HEREDOC)
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