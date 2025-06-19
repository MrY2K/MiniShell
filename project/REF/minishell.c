/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achoukri <achoukri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2025/06/16 17:05:33 by achoukri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}


/* Debug print for the t_splitor linked list */
void debug_print_splitor_list(t_splitor *list)
{
    int idx = 0;
    while (list)
    {
        printf("Splitor[%d]:\n", idx);
        printf("  in: %s\n", list->in ? list->in : "(null)");
        printf("  len: %d\n", list->len);
        printf("  type: %d\n", list->type);
        printf("  is_amb: %d\n", list->is_amb);
        printf("  is_exp: %d\n", list->is_exp);
        printf("  state: %d\n", list->state);
        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no splitor nodes)\n");
}

/* Debug print for the t_command linked list */
void debug_print_command_list(t_command *list)
{
    int idx = 0;
    while (list)
    {
        printf("Command[%d]:\n", idx);
        printf("  content: %s\n", list->content ? list->content : "(null)");

        if (list->arg)
        {
            printf("  arguments:");
            for (int i = 0; list->arg[i] != NULL; i++)
                printf(" [%s]", list->arg[i]);
            printf("\n");
        }
        else
            printf("  arguments: (none)\n");

        printf("  is_amb: %d\n", list->is_amb);
        printf("  is_exp: %d\n", list->is_exp);
        printf("  is_pipe: %d\n", list->is_pipe);
        printf("  len: %d\n", list->len);

        // If you wish to display redirections, heredocs, or env arr, add that here.
        if (list->doc)
            printf("  redirections are present\n");
        else
            printf("  redirections: (none)\n");

        if (list->her)
            printf("  heredocs are present\n");
        else
            printf("  heredocs: (none)\n");

        if (list->ar_env)
        {
            printf("  env array:");
            for (int i = 0; list->ar_env[i] != NULL; i++)
                printf(" [%s]", list->ar_env[i]);
            printf("\n");
        }
        else
            printf("  env array: (none)\n");

        list = list->next;
        idx++;
    }
    if (idx == 0)
        printf("(no command nodes)\n");
}

void	ft_initialize(t_splitor *x, t_command **cmd, t_environment **my_env)
{
	if (x != NULL && my_env != NULL)
	{
		debug_print_splitor_list(x);
		ft_command(&x, cmd, *my_env);
		debug_print_command_list(*cmd);
		ft_exute(my_env, *cmd);
	}
	ft_free_command(cmd);
	ft_free_lexer(&x);
}

void	ft_reader(t_splitor *x, t_command *cmd, t_environment **my_env)
{
	char	*str_input;

	while (1)
	{
		str_input = readline("minishell ");
		if (!str_input)
		{
			printf("exit\n");
			exit(g_exit_status);
		}
		if (ft_strlen(str_input) > 0)
			add_history(str_input);
		if (ft_lexer(str_input, &x))
		{
			g_exit_status = 258;
			ft_putstr_fd("minishell: syntax error\n", 2);
			ft_free_lexer(&x);
		}
		else
			ft_initialize(x, &cmd, my_env);
		cmd = NULL;
		x = NULL;
		free(str_input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_splitor		*x;
	t_environment	*my_env;
	t_command		*cmd;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	(void)ac;
	(void)av;
	my_env = NULL;
	my_env = ft_stock_envarment(env);
	using_history();
	x = NULL;
	cmd = NULL;
	ft_reader(x, cmd, &my_env);
	ft_free_env(&my_env);
	return (g_exit_status);
}
