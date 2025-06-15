
#include "../includes/minishell.h"


/* Debug print for the t_token linked list */
void debug_print_token_list(t_token *list)
{
    int idx = 0;
    while (list)
    {
        // Print index, value (in quotes), len, type, state
        // If value may contain non-printables, consider printing repr; here we assume printable.
        printf("Token[%d]: value=\"%s\" len=%d type=%d state=%d\n",
               idx,
               list->value ? list->value : "(null)",
               list->len,
               list->type,
               list->state);
        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no tokens)\n");
}

/* Helper to print a redirection type as string, if you wish */
static const char *redir_type_to_str(t_token_type type)
{
    // Adjust these cases according to your enum definitions
    if (type == '<')               return "<";
    if (type == '>')               return ">";
    if (type == TOKEN_REDIR_APPEND) return ">>";  // or your enum constant
    if (type == TOKEN_HEREDOC)     return "<<";  // or your enum constant
    // If type is stored differently, add cases here
    // Fallback:
    static char buf[8];
    if (type >= 32 && type < 127) {
        snprintf(buf, sizeof(buf), "%c", (char)type);
        return buf;
    }
    snprintf(buf, sizeof(buf), "%d", (int)type);
    return buf;
}

/* Debug print for the t_cmd linked list */
void debug_print_cmd_list(t_cmd *list)
{
    int idx = 0;
    while (list)
    {
        printf("=== Command[%d] ===\n", idx);
        // main_cmd
        if (list->main_cmd && *list->main_cmd)
            printf(" main_cmd: \"%s\"\n", list->main_cmd);
        else
            printf(" main_cmd: (null or empty)\n");
        // arguments array
        if (list->argument)
        {
            printf(" argv:");
            for (int i = 0; list->argument[i]; i++)
                printf(" [\"%s\"]", list->argument[i]);
            printf("\n");
        }
        else
        {
            printf(" argv: (none)\n");
        }
        // arg_len if meaningful
        printf(" arg_len: %d\n", list->arg_len);
        // flags
        printf(" has_ambiguous: %d\n", list->has_ambiguous);
        printf(" pipe: %d\n", list->pipe);
        printf(" needs_expansion: %d\n", list->needs_expansion);
        // environment array if present
        if (list->env_arr)
        {
            printf(" env_arr:");
            for (int i = 0; list->env_arr[i]; i++)
                printf(" [\"%s\"]", list->env_arr[i]);
            printf("\n");
        }
        else
            printf(" env_arr: (none)\n");
        // redirections
        if (list->redirections)
        {
            printf(" redirections:\n");
            for (t_redirect *r = list->redirections; r; r = r->next)
            {
                const char *sym = redir_type_to_str(r->type);
                printf("   %s  file=\"%s\"  is_ambiguous=%d\n",
                       sym,
                       r->file_path ? r->file_path : "(null)",
                       r->is_ambig);
            }
        }
        else
            printf(" redirections: (none)\n");
        // heredocs
        if (list->heredoc)
        {
            printf(" heredocs:\n");
            for (t_heredoc *h = list->heredoc; h; h = h->next)
            {
                printf("   delimiter=\"%s\"  her_file=\"%s\"  fd=%d  expand=%d\n",
                       h->delimiter ? h->delimiter : "(null)",
                       h->her_file ? h->her_file : "(null)",
                       h->fd,
                       h->expand);
            }
        }
        else
            printf(" heredocs: (none)\n");

        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no command nodes)\n");
}