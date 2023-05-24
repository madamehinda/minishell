/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:06:48 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/05 10:11:40 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_builltin(t_cmd *exec_cmd, t_data *data)
{
	int	fd;

	if (exec_cmd->fd_out > 1)
	{
		fd = dup(1);
		dup2(exec_cmd->fd_out, 1);
	}
	is_builtin(data, exec_cmd->cmd, exec_cmd);
	if (exec_cmd->fd_out > 1)
	{
		dup2(fd, 1);
		close(fd);
	}
}

void	redir_one_cmd(t_cmd *cmd_exec)
{
	if (cmd_exec->fd_in > 2)
		dup2(cmd_exec->fd_in, 0);
	if (cmd_exec->fd_out > 2)
		dup2(cmd_exec->fd_out, 1);
}

void	redir_begin(t_data *data, t_cmd *cmd_exec, int i)
{
	if (cmd_exec->fd_in != -1)
		dup2(cmd_exec->fd_in, 0);
	else
		dup2(0, 0);
	if (cmd_exec->fd_out != -1)
		dup2(cmd_exec->fd_out, 1);
	else
		dup2(data->pfd[i][1], 1);
}

void	redir_middle(t_data *data, t_cmd *cmd_exec, int i)
{
	if (cmd_exec->fd_in != -1)
		dup2(cmd_exec->fd_in, 0);
	else
		dup2(data->pfd[i - 1][0], 0);
	if (cmd_exec->fd_out != -1)
		dup2(cmd_exec->fd_out, 1);
	else
		dup2(data->pfd[i][1], 1);
}

void	redir_end(t_data *data, t_cmd *cmd_exec, int i)
{
	if (cmd_exec->fd_in != -1)
		dup2(cmd_exec->fd_in, 0);
	else
		dup2(data->pfd[i - 1][0], 0);
	if (cmd_exec->fd_out != -1)
		dup2(cmd_exec->fd_out, 1);
	else
	{
		cmd_exec->fd_out = 1;
		dup2(cmd_exec->fd_out, 1);
	}
}
