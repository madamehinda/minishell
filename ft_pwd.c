/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:42:38 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/06 14:33:09 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		g_exit_code = 1;
		write(2, "pwd: error retrieving current directory: getcwd: \
		cannot access parent directories: No such file or directory\n",
			112);
		free(pwd);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
