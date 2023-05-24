/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:55:49 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/04 17:47:41 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(char *argv)
{
	int	i;

	i = 1;
	if (argv[0] == '-')
	{
		while (argv[i] == 'n')
			i++;
		if (argv[i] == '\0')
			return (1);
	}
	return (0);
}

int	ft_echo(char **argv, t_data *mini, t_cmd *exec_cmd)
{
	int	i;
	int	flag;

	(void)mini;
	i = 1;
	flag = 0;
	while (i < exec_cmd->argc && ft_check(argv[i]))
	{
		i++;
		flag = 1;
	}
	while (i < exec_cmd->argc)
	{
		ft_putstr_fd(argv[i], 1);
		if (i + 1 < exec_cmd->argc)
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
	{
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
