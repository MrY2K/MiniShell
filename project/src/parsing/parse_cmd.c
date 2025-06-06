#include "../includes/minishell.h"

void	parse_command(t_token *token, t_cmd *cmd, t_env **env)
{
    t_token	*current;
    int		arg_index;
    char	*expanded;

    current = token;
    arg_index = 0;
    // Initialize command structure fields
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->append = 0;
    
    // Iterate through tokens to populate the command structure
    while (current)
    {
        if (current->type == TOKEN_WORD)
        {
            // Expand environment variables in the token value
            expanded = expand_variables(current->value, env);
            // Store the argument string in the command structure (assume ft_strdup is available)
            cmd->args[arg_index++] = ft_strdup(expanded);
            free(expanded);
        }
        else if (current->type == TOKEN_REDIRECT_IN)
        {
            // Input redirection: next token holds the filename
            if (current->next)
            {
                cmd->infile = ft_strdup(current->next->value);
                current = current->next;
            }
        }
        else if (current->type == TOKEN_REDIRECT_OUT)
        {
            // Output redirection (overwrite)
            if (current->next)
            {
                cmd->outfile = ft_strdup(current->next->value);
                cmd->append = 0;
                current = current->next;
            }
        }
        else if (current->type == TOKEN_APPEND)
        {
            // Output redirection (append)
            if (current->next)
            {
                cmd->outfile = ft_strdup(current->next->value);
                cmd->append = 1;
                current = current->next;
            }
        }
        // Process further token types if needed
        
        current = current->next;
    }
    // Null terminate the arguments array
    cmd->args[arg_index] = NULL;
}
