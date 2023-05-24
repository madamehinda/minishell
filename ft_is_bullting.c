/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_bullting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:31:19 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/05 09:44:32 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *mini, char **argv, t_cmd *exec_cmd)
{
	g_exit_code = 0;
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit(mini, argv, exec_cmd), g_exit_code);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(), g_exit_code);
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		if (ft_cd(argv, mini) == 1)
			g_exit_code = 1;
		return (g_exit_code);
	}
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv, mini, exec_cmd), g_exit_code);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, mini, exec_cmd), g_exit_code);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(mini, exec_cmd, argv), g_exit_code);
	else if (ft_strcmp(argv[0], "env") == 0 && !argv[1])
		return (ft_env(mini), g_exit_code);
	return (0);
}

int	is_builtin_pipe(t_data *mini, char **argv, t_cmd *exec_cmd, t_cmd *head)
{
	g_exit_code = 0;
	if (ft_strcmp(argv[0], "exit") == 0)
		return (ft_exit_pipe(mini, argv, exec_cmd, head), g_exit_code);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (ft_pwd(), g_exit_code);
	else if (ft_strcmp(argv[0], "cd") == 0)
	{
		if (ft_cd(argv, mini) == 1)
			g_exit_code = 1;
		return (g_exit_code);
	}
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (ft_echo(argv, mini, exec_cmd), g_exit_code);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (ft_export(argv, mini, exec_cmd), g_exit_code);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (ft_unset(mini, exec_cmd, argv), g_exit_code);
	else if (ft_strcmp(argv[0], "env") == 0 && !argv[1])
		return (ft_env(mini), g_exit_code);
	return (0);
}

int	builtin_env(char **argv)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(argv[0], "env") == 0)
		return (1);
	else
		return (0);
}
