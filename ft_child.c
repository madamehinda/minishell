/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:46:23 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/10 14:55:00 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exeve_one(t_data *data, t_cmd *cmd_exec)
{
	ft_close_fd(cmd_exec);
	ft_lstclear_command(&cmd_exec);
	ft_free(data->env);
}

void	ft_free_pipe(t_data *data, t_cmd *cmd_exec)
{
	ft_close_fd(cmd_exec);
	ft_free(data->env);
	free_pfd(data);
}

void	fct_exeve(t_cmd *cmd_exec, t_data *data)
{
	if (cmd_exec->argc > 0 && ft_strlen(cmd_exec->cmd[0]) > 0)
	{
		if (cmd_exec->cmd[0] && get_cmd(cmd_exec->cmd[0], data->env)
			&& !cmd_exec->status)
		{
			execve(get_cmd(cmd_exec->cmd[0], data->env), cmd_exec->cmd,
				data->env);
		}
		if (cmd_exec->cmd[0] && !get_cmd(cmd_exec->cmd[0], data->env)
			&& !cmd_exec->status)
		{
			err_msg(cmd_exec->cmd[0], "command not found");
		}
	}
	else
		err_msg(cmd_exec->cmd[0], "command not found");
}

int	verif_exit_code(t_cmd *head, t_cmd *cmd_exec, t_data *data)
{
	if (g_exit_code != 130)
	{
		g_exit_code = 1;
		ft_free_pipe(data, cmd_exec);
		ft_lstclear_command(&head);
		return (g_exit_code);
	}
	else
	{
		g_exit_code = 130;
		ft_free_pipe(data, cmd_exec);
		ft_lstclear_command(&head);
		return (g_exit_code);
	}
}

int	child(t_cmd *cmd_exec, t_data *data, t_cmd *head)
{
	if (!cmd_exec->status && cmd_exec->argc > 0)
	{
		if (builtin_env(cmd_exec->cmd) == 1)
		{
			g_exit_code = is_builtin_pipe(data, cmd_exec->cmd, cmd_exec, head);
			ft_free_pipe(data, cmd_exec);
			ft_lstclear_command(&head);
			return (g_exit_code);
		}
		else if (!builtin_env(cmd_exec->cmd))
		{
			g_exit_code = verif(cmd_exec, data);
			ft_free_pipe(data, cmd_exec);
			ft_lstclear_command(&head);
			return (g_exit_code);
		}
	}
	else
	{
		g_exit_code = verif_exit_code(head, cmd_exec, data);
		return (g_exit_code);
	}
	return (0);
}
