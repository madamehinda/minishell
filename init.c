/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:44:49 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:41:26 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	dup_env(t_data *data, char **env)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (env[++i] != NULL)
		size++;
	data->env = ft_calloc(size + 1, sizeof(char **));
	if (!data->env)
		return (0);
	i = -1;
	while (env[++i] != NULL)
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			return (0);
	}
	i = -1;
	while (data->env[++i] != NULL)
		size++;
	return (1);
}

int	init_struct(t_data *data, char **env)
{
	data->line = NULL;
	data->cmds = NULL;
	data->env = NULL;
	data->token = NULL;
	data->expand = NULL;
	data->nbr_cmd = 0;
	data->nbr_pipe = 0;
	data->pfd = NULL;
	if (dup_env(data, env) == FALSE)
	{
		printf("error : initialization of environment");
		return (0);
	}
	return (1);
}

void	ft_init_mini(t_data *data)
{
	data->line = replace(data);
	data->token = read_input(data->line);
	data->cmds = parse_cmd_table(data, data->token);
	data->nbr_cmd = ft_count_list(data->cmds);
	data->nbr_pipe = data->nbr_cmd - 1;
}

int	ft_count_list(t_cmd *cur)
{
	t_cmd	*cmd_list;
	int		count;

	cmd_list = cur;
	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

int	ft_count_word(t_token *lexer)
{
	t_token	*tmp;
	int		count;

	tmp = lexer;
	count = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}
