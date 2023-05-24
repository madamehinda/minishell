/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 15:49:55 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/02 13:35:37 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void	ft_lstdelone_token(t_token *lst, void (*del)(void *))
{
	del(lst->value);
	free(lst);
}

void	ft_lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone_token((*lst), del);
		*lst = tmp;
	}
	*lst = NULL;
}
