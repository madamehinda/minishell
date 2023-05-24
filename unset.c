/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:08:06 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/10 14:52:22 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_data *mini, t_cmd *cmd, char **argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (j < cmd->argc)
	{
		if (!ft_strchr(argv[j], '='))
		{
			i = 0;
			while ((mini->env[i]) && ft_strncmp(mini->env[i], argv[j],
					ft_strlen(argv[j])))
				i++;
			if (i == ft_strlen_mat(mini->env))
				return ;
			else
				realloc_unset(mini, argv[j]);
			j++;
		}
		else
		{
			g_exit_code = 1;
			j++;
		}
	}
}

void	util_unset(t_data *mini, int i, int j, char **temp)
{
	while (mini->env[i])
	{
		temp[j] = mini->env[i];
		j++;
		i++;
	}
	free(mini->env);
	mini->env = temp;
}

void	realloc_unset(t_data *mini, char *str)
{
	int		i;
	int		j;
	int		u;
	char	**temp;

	i = 0;
	j = 0;
	u = 0;
	temp = malloc(sizeof(char *) * (ft_strlen_mat(mini->env)));
	if (!temp)
		return ;
	temp[ft_strlen_mat(mini->env) - 1] = 0;
	while ((mini->env[u]) && ft_strncmp(mini->env[u], str, ft_strlen(str)))
		u++;
	while (i < u)
	{
		temp[j] = mini->env[i];
		j++;
		i++;
	}
	free(mini->env[u]);
	i++;
	util_unset(mini, i, j, temp);
}

int	verif(t_cmd *cmd_exec, t_data *data)
{
	struct stat		st;
	int				stat;
	unsigned int	mode;
	char			*cmd;

	cmd = cmd_exec->cmd[0];
	stat = lstat(cmd, &st);
	mode = st.st_mode & S_IFMT;
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, F_OK & X_OK) == 0)
			execve(cmd, cmd_exec->cmd, data->env);
		if (stat == -1)
			return (err_msg(cmd, "No such file or directory"), 127);
		if (access(cmd, X_OK) == 0 && (mode != S_IFLNK || mode != S_IFREG))
			return (err_msg(cmd, "Is a directory"), 126);
		if (access(cmd, X_OK) != 0)
			return (err_msg(cmd, "Permission denied"), 126);
	}
	if (access(cmd, F_OK & X_OK) == 0)
		return (execve(cmd, cmd_exec->cmd, data->env), 127);
	else
		return (fct_exeve(cmd_exec, data), 127);
	return (0);
}
