/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:40:45 by achoukri          #+#    #+#             */
/*   Updated: 2025/05/25 15:10:33 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <string.h>

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



// ************   Exit ********************



// int main(void)
// {
//     t_minibash bash = {.exit_status = 0};
//     t_cmd cmd;

//     // Test 1: No arguments → should exit with bash.exit_status (0)
//     // cmd.argument = NULL;
// 	// bash.exit_status = 137;
//     // // printf("Test 1: No arguments, expect exit code 0\n");
//     // builtin_exit(&cmd, &bash);

//     // Test 2: Valid numeric argument "42"
//     // char *arg1[] = {"42", NULL};
//     // cmd.argument = arg1;
//     // //printf("Test 2: Argument '42', expect exit code 42\n");
//     // builtin_exit(&cmd, &bash);

//     // Test 3: Invalid numeric argument "abc"
//     // char *arg2[] = {"xc", NULL};
//     // cmd.argument = arg2;
//     // bash.exit_status = 0;
//     // //printf("Test 3: Argument 'abc', expect error and exit code 255\n");
//     // builtin_exit(&cmd, &bash);

//     // // Test 4: Too many arguments "1", "2"
//     // char *arg3[] = {"1", "2", NULL};
//     // cmd.argument = arg3;
//     // bash.exit_status = 0;
//     // printf("Test 4: Too many args, expect error and return without exit\n");
//     // //builtin_exit(&cmd, &bash);
//     // printf("Returned from exit due to too many arguments\n");

//     // // Test 5: Double sign prefix "++1"
//     // char *arg4[] = {"++1", NULL};
//     // cmd.argument = arg4;
//     // printf("Test 5: Double sign prefix '++1', expect error and exit 255\n");
//     // // builtin_exit(&cmd, &bash);

//     return 0;
// }





// *********************  unset ****************




#include <stdio.h>
#include <stdlib.h>
#include "prototypes.h"

// void print_env(t_env *env)
// {
// 	while (env)
// 	{
// 		printf("%s=%s\n", env->name, env->value);
// 		env = env->next;
// 	}
// }

// int main(void)
// {
// 	t_minibash bash;

// 	// Fake environment like real envp[]
// 	char *fake_env[] = {
// 		"USER=abubakar",
// 		"HOME=/home/abubakar",
// 		"PATH=/usr/bin",
// 		"EDITOR=vim",
// 		NULL
// 	};

// 	// Initialize the bash.env linked list
// 	initialize_environment(&bash, fake_env);

// 	// Print before unset
// 	printf("Before unset:\n");
// 	print_env(bash.env);

// 	// Simulate: unset HOME PATH
// 	char *args[] = {"unset", "HOME", "PATH", NULL};
// 	builtin_unset(&bash, args);

// 	// Print after unset
// 	printf("\nAfter unset:\n");
// 	print_env(bash.env);

// 	return 0;
// }


// *********  export *****************


// void	free_env_list(t_env *env)
// {
// 	t_env	*tmp;

// 	while (env)
// 	{
// 		tmp = env;
// 		env = env->next;
// 		free(tmp->name);
// 		free(tmp->value);
// 		free(tmp);
// 	}
// }



// int	main(void)
// {
// 	t_minibash	bash;
// 	t_cmd		cmd;
// 	t_env		*env = NULL;

// 	// Initialize the shell environment
// 	bash.env = env;
// 	bash.exit_status = 0;

// 	// Simulate input: export VAR1=value1 VAR2=value2
// 	char *args[] = {
// 		"VAR1=\"ls -la\"",
// 		"VAR2=value2",
// 		"_VALID=ok",
// 		"9INVALID=bad",    // invalid
// 		"=missingname",    // invalid
// 		"ALSO_OK",
// 		"b=ls",   // just a name, no value
// 		NULL
// 	};
// 	cmd.argument = args;

// 	// Call the export function
// 	export(&bash, &cmd);

// 	// Show results after export
// 	printf("\n-- After Export --\n");
// 	display_exported_variable(&bash);

// 	return (bash.exit_status);
// }




/************	Test Lexer		**************** */

char *token_type_to_str(t_token_type type)
{
    if (type == TOKEN_WORD)
        return "WORD";
    return "UNKNOWN";
}


const char *state_to_str(t_state state)
{
    if (state == Normal)
        return "Normal";
    if (state == Single)
        return "Single";
    if (state == Double)
        return "Double";
    return "NUL";
}

int main(void)
{
    char *input = "echo \"hello world\" | grep 'o'";
    t_token *tokens = NULL;

    if (lexer(input, &tokens) != 0)
    {
        printf("Lexer error\n");
        return 1;
    }

    t_token *current = tokens;
    while (current)
    {
        printf("Token: type=%s, value='%s', len=%d, state=%s\n",
            token_type_to_str(current->type),
            current->value,
            current->len,
            state_to_str(current->state));
        current = current->next;
    }


    return 0;
}
