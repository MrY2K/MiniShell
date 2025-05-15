/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/15 14:03:24 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// ******************* echo  *************



// int	main(int argc, char **argv)
// {
// 	t_cmd	cmd;

// 	if (argc < 2)
// 		return (1);

// 	cmd.man_cmd = argv[1]; 
// 	cmd.argument = &argv[2];   // Skip the command name, pass the rest & 

// 	if (ft_strncmp(cmd.man_cmd, "echo", 4) == 0)
// 		echo(&cmd);
// 	else
// 		write (1, "tzzz", 5);
// 	return (0);
// }


// ******************* cd   *************

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minibash	bash;
// 	t_cmd		cmd;
// 	char		*pwd;
// 	char		*oldpwd;

// 	(void)argc;
// 	(void)argv;

// 	// 1. Initialize the bash struct
// 	ft_memset(&bash, 0, sizeof(t_minibash));
// 	initialize_environment(&bash, envp);

// 	// 2. Manually simulate a 'cd' command
// 	cmd.argument = malloc(sizeof(char *) * 3);
// 	if (!cmd.argument)
// 		return (1);
// 	cmd.argument[0] = ft_strdup("cd");
// 	cmd.argument[1] = ft_strdup("..");  // change directory to parent
// 	cmd.argument[2] = NULL;
// 	cmd.man_cmd = ft_strdup("cd");

// 	// 3. Call your cd function
// 	cd(&cmd, &bash);  // fixed order

// 	// 4. Print updated env
// 	pwd = get_environment("PWD", &bash);
// 	oldpwd = get_environment("OLDPWD", &bash);

// 	printf("PWD = %s\n", pwd);
// 	printf("OLDPWD = %s\n", oldpwd);

// 	free(pwd);
// 	free(oldpwd);
// 	// also free cmd.argument and cmd.man_cmd if needed

// 	return (0);
// }



// ******************* pwd  *************


// int main(void) 
// {
//     t_minibash bash;
    
//     /* Initialize the minibash structure */
//     bash.env = NULL;
//     bash.exit_status = -1; /* Set to -1 to verify it changes */
    
//     printf("Testing pwd command:\n");
//     printf("--------------------\n");
    
//     /* Call the pwd function */
//     pwd(&bash);
    
//     /* Verify the exit status was updated */
//     printf("\nExit status after pwd: %d\n", bash.exit_status);
    
//     return 0;
// }



// ******************* env  *************



// t_env *create_manual_env_node(char *name, char *value)
// {
// 	t_env *node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (NULL);
// 	node->name = name ? ft_strdup(name) : NULL;
// 	node->value = value ? ft_strdup(value) : NULL;
// 	node->next = NULL;
// 	return node;
// }
// #include <string.h>
// int main(int argc, char **argv, char **envp)
// {
// 	(void) argc;
// 	(void) argv;
// 	t_minibash bash;
// 	t_env *broken1, *broken2, *last;

// 	// Initialize struct
// 	memset(&bash, 0, sizeof(t_minibash));

// 	// ✅ Load real env using your function
// 	initialize_environment(&bash, envp);

// 	// 🔴 Add edge cases manually (NULL name or NULL value)
// 	broken1 = create_manual_env_node(NULL, "something");
// 	broken2 = create_manual_env_node("NO_VALUE", NULL);

// 	// Find last node in the list
// 	last = bash.env;
// 	while (last && last->next)
// 		last = last->next;

// 	// Append broken env nodes
// 	if (last)
// 		last->next = broken1;
// 	broken1->next = broken2;

// 	// Call your builtin
// 	printf("======= ENV OUTPUT =======\n");
// 	env(&bash);
// 	printf("Exit status: %d\n", bash.exit_status);

// 	// Cleanup (free memory)
// 	t_env *tmp;
// 	while (bash.env)
// 	{
// 		tmp = bash.env;
// 		bash.env = bash.env->next;
// 		if (tmp->name) free(tmp->name);
// 		if (tmp->value) free(tmp->value);
// 		free(tmp);
// 	}
// 	return 0;
// }



