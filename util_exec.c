/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:07:20 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/06 15:44:30 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	err_msg(char *cmd, char *msg)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
}

int	ft_no_path(char **env)
{
	int	i;

	i = 0;
	while ((env[i]) && !ft_strnstr(env[i], "PATH", 4))
		i++;
	return (i);
}

char	**ft_get_path(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(env[i], "PATH", 4))
		i++;
	paths = ft_split(env[i] + 5, ':');
	return (paths);
}

char	*get_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	i = ft_no_path(envp);
	if (i == ft_strlen_mat(envp))
		return (0);
	else
	{
		paths = ft_get_path(envp);
		i = -1;
		while (paths[++i])
		{
			slash = ft_strjoinn(paths[i], "/");
			path = ft_strjoinn(slash, cmd);
			free(slash);
			if (!access(path, F_OK))
				return (ft_free(paths), path);
			free(path);
		}
		ft_free(paths);
	}
	return (0);
}
