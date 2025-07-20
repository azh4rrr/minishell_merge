/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azhar <azhar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 12:36:03 by ymouchta          #+#    #+#             */
/*   Updated: 2025/07/20 18:51:50 by azhar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals_main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_herdoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

void	set_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

/*
 * To prevent "^C" from being displayed, make sure to use
 * sigaction with the SA_RESTART flag and do NOT set the
 * terminal to echo control characters (ECHOCTL).
 *
 * In your main function or initialization code, add:
 *
 * struct termios term;
 * tcgetattr(STDIN_FILENO, &term);
 * term.c_lflag &= ~ECHOCTL;
 * tcsetattr(STDIN_FILENO, TCSANOW, &term);
 *
 * This disables echoing "^C" when Ctrl+C is pressed.
 */
