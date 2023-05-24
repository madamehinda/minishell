/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:06:57 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 10:08:46 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

void	if_redir_parse(t_token **cur, t_cmd *ret)
{
	if ((*cur)->type == STD_IN)
		if_stdin(cur, ret);
	else if ((*cur)->type == TRUNC)
		if_trunc(cur, ret);
	else if ((*cur)->type == APPEND)
		if_append(cur, ret);
}

void	if_stdin(t_token **cur, t_cmd *ret)
{
	ret->status = handle_input(ret, (*cur)->value);
	if (ret->status != 0)
	{
		while ((*cur) && (*cur)->next && (*cur)->next->type != PIPE)
		{
			(*cur) = (*cur)->next;
		}
	}
}

void	if_trunc(t_token **cur, t_cmd *ret)
{
	ret->status = handle_output_simple(ret, (*cur)->value);
	if (ret->status != 0)
	{
		while ((*cur) && (*cur)->next && (*cur)->next->type != PIPE)
		{
			(*cur) = (*cur)->next;
		}
	}
}

void	if_append(t_token **cur, t_cmd *ret)
{
	ret->status = handle_output_double(ret, (*cur)->value);
	if (ret->status != 0)
	{
		while ((*cur) && (*cur)->next && (*cur)->next->type != PIPE)
		{
			(*cur) = (*cur)->next;
		}
	}
}

int	is_redir_parse(t_token *cur)
{
	if (cur->type == STD_IN || cur->type == TRUNC || cur->type == APPEND)
		return (1);
	return (0);
}
