/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:33:30 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 14:09:21 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

void	ft_free_mini(t_cmd *exec_cmd, t_data *data)
{
	(void)exec_cmd;
	if (data->pfd)
		free_pfd(data);
	ft_free(data->env);
}

void	ft_lstdelone_token(t_token *lst)
{
	free(lst->value);
	free(lst);
}

void	ft_lstclear_token(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_token((*lst));
		*lst = tmp;
	}
	*lst = NULL;
}

void	ft_lstdelone_command(t_cmd *lst)
{
	if (lst->argc != 0)
		ft_free(lst->cmd);
	else
		free(lst->cmd);
	free(lst);
}

void	ft_lstclear_command(t_cmd **lst)
{
	t_cmd	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_close_fd(*lst);
		ft_lstdelone_command((*lst));
		*lst = tmp;
	}
	*lst = NULL;
}
