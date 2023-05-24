/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:13:44 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/06 15:32:12 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	realloc_env_be(t_data *mini, char *str)
{
	char	*var;
	char	*val;
	char	*temp;
	int		i;

	i = 0;
	var = ft_select(str);
	while (ft_strncmp(mini->env[i], var, ft_strlen(var)))
		i++;
	free(var);
	if (is_plus(str))
	{
		val = ft_select1(str);
		temp = ft_strjoin(mini->env[i], val);
		free(val);
		mini->env[i] = temp;
	}
	else if (!is_plus(str))
	{
		free(mini->env[i]);
		temp = strdup(str);
		mini->env[i] = temp;
	}
	return ;
}

char	*ft_get_add_env(t_data *mini, char *str)
{
	char	*val;
	char	*temp;
	int		i;

	val = ft_select1(str);
	i = ft_strlen_mat(mini->env);
	if (val && !is_plus(str))
	{
		temp = ft_strdup(str);
		mini->env[i] = temp;
		free(val);
	}
	else if (val && is_plus(str))
	{
		temp = strdup_plus(str);
		mini->env[i] = temp;
		free(val);
	}
	return (mini->env[i]);
}

void	util_get_env(t_data *mini, char **argv, int *i, int *j)
{
	char	*var;

	var = NULL;
	*i = 0;
	var = ft_select(argv[*j]);
	while (mini->env[*i] && (ft_strncmp(mini->env[*i], var, ft_strlen(var))))
		(*i)++;
	if (*i == ft_strlen_mat(mini->env))
		realloc_env(mini, argv[*j]);
	else
		realloc_env_be(mini, argv[*j]);
	free(var);
	(*j)++;
}

void	get_env(t_data *mini, t_cmd *cmd, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < cmd->argc)
	{
		if (is_export(argv[j]))
		{
			util_get_env(mini, argv, &i, &j);
		}
		else
		{
			printf("export: `%s': not a valid identifier\n", argv[j]);
			g_exit_code = 1;
			j++;
		}
	}
}

void	ft_export(char **argv, t_data *mini, t_cmd *exec_cmd)
{
	if (exec_cmd->argc == 1)
	{
		print_export(mini);
	}
	else
		get_env(mini, exec_cmd, argv);
	return ;
}
