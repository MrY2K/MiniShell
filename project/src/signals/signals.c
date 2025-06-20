/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:07:19 by achoukri          #+#    #+#             */
/*   Updated: 2025/06/20 09:56:05 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void  sigint_handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);			 // ← explicit newline
	rl_on_new_line();							/* say “we’re on a new empty line” */
	rl_replace_line("", 0);				/* clear current buffer            */
	rl_redisplay();							/* show fresh prompt               */
}

void	signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT,  sigint_handler);   /* Ctrl-C  */
	signal(SIGQUIT, SIG_IGN);          /* Ctrl-\  */
}
