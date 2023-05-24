/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 14:21:30 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/06 15:28:07 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_mat(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		y++;
	}
	return (y);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	realloc_env(t_data *mini, char *str)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	while (mini->env[i])
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (!temp)
		return ;
	temp[i + 1] = 0;
	while (mini->env[j])
	{
		temp[j] = mini->env[j];
		j++;
	}
	temp[i] = ft_get_add_env(mini, str);
	free(mini->env);
	mini->env = temp;
}

int	ft_env(t_data *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		printf("%s\n", mini->env[i]);
		i++;
	}
	return (0);
}

int	print_export(t_data *mini)
{
	int		i;
	char	*var;
	char	*val;

	i = 0;
	while (mini->env[i])
	{
		var = ft_select(mini->env[i]);
		val = ft_select1(mini->env[i]);
		printf("declare -x ");
		printf("%s", var);
		printf("\"%s\"\n", val);
		free(var);
		free(val);
		i++;
	}
	return (0);
}
