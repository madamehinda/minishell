/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:45:41 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:27:13 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	is_even(int num)
{
	return (!(num & 1));
}

int	ft_quotes(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			count++;
		i++;
	}
	if (is_even(count))
	{
		return (1);
		printf("The number is even.");
	}
	return (0);
}

void	ft_free_exit(t_cmd *exec_cmd, t_data *data)
{
	ft_lstclear_command(&exec_cmd);
	ft_free(data->env);
}

void	ft_free_exit_pipe(t_cmd *exec_cmd, t_data *data)
{
	(void)exec_cmd;
	free_pfd(data);
	ft_free(data->env);
}

int	is_plus(char *str)
{
	if (ft_strchr(str, '+'))
		return (1);
	return (0);
}
