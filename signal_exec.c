/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:06:27 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/04 16:27:02 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_nl(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	child_signal(int num)
{
	if (num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
	if (num == SIGQUIT)
		g_exit_code = 131;
}

void	hd_sig_child(int num)
{
	(void)num;
	write(2, "\n", 1);
	close(0);
	g_exit_code = 130;
}

void	signal_fork(void)
{
	signal(SIGINT, child_signal);
	signal(SIGQUIT, child_signal);
}

void	father(int status)
{
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_putstr_fd("\n", 2);
			g_exit_code = 130;
		}
		else if (WTERMSIG(status) == 3)
		{
			ft_putstr_fd(" Quit (core dumped)\n", 2);
			g_exit_code = 131;
		}
		else
			g_exit_code = 128 + WTERMSIG(status);
	}
}
