/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:11:04 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/10 12:39:23 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

void	sig_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 130;
}

static void	signint_heredoc(int sig, siginfo_t *info, void *ucontext)
{
	char	c;

	(void)info;
	(void)ucontext;
	(void)sig;
	c = '\n';
	g_exit_code = 130;
	ioctl(STDOUT_FILENO, TIOCSTI, &c);
}

void	setup_signal_heredoc(void)
{
	struct sigaction	sa;
	struct sigaction	quit_sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &signint_heredoc;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, 0);
	sigemptyset(&quit_sa.sa_mask);
	quit_sa.sa_handler = SIG_IGN;
	quit_sa.sa_flags = 0;
	sigaction(SIGQUIT, &quit_sa, NULL);
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	if (sig_int == HER)
		signal(SIGINT, SIG_IGN);
	if (sig_int == SHE)
		signal(SIGINT, sig_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == HER)
		signal(SIGQUIT, SIG_IGN);
	if (sig_quit == SHE)
		signal(SIGQUIT, sig_handler);
}
