/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:22:00 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/10 14:52:59 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_cmd *exec_cmd, t_data *data)
{
	t_cmd	*head;

	head = exec_cmd;
	if (data->nbr_cmd == 1 && exec_cmd->status == 0 && exec_cmd->argc > 0)
	{
		if (builtin_env(exec_cmd->cmd) == 1)
			redir_builltin(exec_cmd, data);
		else if (!builtin_env(exec_cmd->cmd))
			exec_one_cmd(exec_cmd, data);
	}
	else if (exec_cmd->status != 0 && g_exit_code != 130 && data->nbr_cmd == 1)
		g_exit_code = 1;
	else if (exec_cmd->status != 0 && g_exit_code == 130 && data->nbr_cmd == 1)
		g_exit_code = 130;
	else if (data->nbr_cmd > 1)
		exec_pipe(exec_cmd, data, head);
	else
		return ;
}

void	open_file(t_data *data, t_cmd *cmd_exec, int i)
{
	if (i == 0)
		redir_begin(data, cmd_exec, i);
	else if (i > 0 && i <= (data->nbr_pipe - 1))
		redir_middle(data, cmd_exec, i);
	else if (i == (data->nbr_pipe))
		redir_end(data, cmd_exec, i);
}

void	exec_one_cmd(t_cmd *cmd_exec, t_data *data)
{
	int	status;

	cmd_exec->pid_one = fork();
	if (cmd_exec->pid_one == -1)
		write(2, "Error Fork\n", 12);
	else if (cmd_exec->pid_one == 0)
	{
		signal_fork();
		redir_one_cmd(cmd_exec);
		ft_close_fd(cmd_exec);
		status = verif(cmd_exec, data);
		free_exeve_one(data, cmd_exec);
		exit(status);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(cmd_exec->pid_one, &status, 0);
		father(status);
	}
	ft_close_fd(cmd_exec);
}

void	fork_pipe(t_data *data, t_cmd *cmd_exec, t_cmd *head)
{
	int	i;
	int	status;

	i = 0;
	while (cmd_exec != NULL)
	{
		cmd_exec->pid = fork();
		if (cmd_exec->pid == -1)
			return (write(2, "Error Fork\n", 12), free(NULL));
		if (cmd_exec->pid == 0)
		{
			signal_fork();
			open_file(data, cmd_exec, i);
			ft_close(data, cmd_exec);
			status = child(cmd_exec, data, head);
			exit(status);
		}
		i++;
		cmd_exec = cmd_exec->next;
	}
}

void	exec_pipe(t_cmd *cmd_exec, t_data *data, t_cmd *head)
{
	int		j;
	int		status;
	t_cmd	*tmp;

	j = 0;
	status = 0;
	tmp = cmd_exec;
	creat_pipes(data);
	fork_pipe(data, cmd_exec, head);
	ft_close(data, tmp);
	while (j < data->nbr_cmd)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(tmp->pid, &status, 0);
		father(status);
		tmp = tmp->next;
		j++;
	}
}
