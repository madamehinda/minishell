/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:25:11 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/10 14:11:02 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(char *str)
{
	int	i;

	g_exit_code = 1;
	if (!str)
		return (0);
	i = 0;
	if (ft_isdigit(str[i]) == 0 && str[i] != '-' && str[i] != '+')
		return (0);
	i++;
	while (ft_isdigit(str[i]) != 0)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

void	ft_many_arg(t_data *mini, t_cmd *cmd)
{
	(void)mini ;
	write(2, "exit: too many arguments\n", 25);
	if (cmd->argc > 1)
	{
		g_exit_code = 1;
	}
	return ;
}

void	ft_exit(t_data *mini, char **cmd, t_cmd *exec_cmd)
{
	if (is_exit(cmd[1]) && ft_strlen_mat(cmd) > 2)
		ft_many_arg(mini, exec_cmd);
	else if (cmd[1] && is_exit(cmd[1]) == 0)
	{
		write(2, "exit : ", 8);
		ft_putstr_fd(cmd[1], 2);
		write(2, ": numeric argument required\n", 29);
		ft_lstclear_command(&exec_cmd);
		ft_free(mini->env);
		exit(2);
	}
	else if (ft_strlen_mat(cmd) == 1)
	{
		write(2, "exit\n", 5);
		ft_lstclear_command(&exec_cmd);
		ft_free(mini->env);
		exit(0);
	}
	else if (cmd[1] && is_exit(cmd[1]))
	{
		g_exit_code = ft_atoi(cmd[1]);
		ft_lstclear_command(&exec_cmd);
		ft_free(mini->env);
		exit(g_exit_code);
	}
}

void	ft_many_arg_pipe(t_data *mini, t_cmd *cmd, t_cmd *head)
{
	(void)mini ;
	(void)head ;
	write(2, "exit: too many arguments\n", 25);
	if (cmd->argc > 1)
	{
		g_exit_code = 1;
	}
	return ;
}

void	ft_exit_pipe(t_data *mini, char **cmd, t_cmd *exec_cmd, t_cmd *head)
{
	if (is_exit(cmd[1]) && ft_strlen_mat(cmd) > 2)
		ft_many_arg(mini, exec_cmd);
	else if (cmd[1] && is_exit(cmd[1]) == 0)
	{
		ft_putstr_fd(cmd[1], 2);
		write(2, ": numeric argument required\n", 29);
		ft_lstclear_command(&head);
		ft_free_exit_pipe(exec_cmd, mini);
		exit(2);
	}
	else if (ft_strlen_mat(cmd) == 1)
	{
		ft_lstclear_command(&head);
		ft_free_exit_pipe(exec_cmd, mini);
		exit(0);
	}
	else if (cmd[1] && is_exit(cmd[1]))
	{
		g_exit_code = ft_atoi(cmd[1]);
		ft_lstclear_command(&head);
		ft_free_exit_pipe(exec_cmd, mini);
		exit(g_exit_code);
	}
}
