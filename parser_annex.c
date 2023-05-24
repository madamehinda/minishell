/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_annex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 10:07:51 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 10:09:24 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

t_cmd	*ft_create_cmd(t_token *cur, t_cmd *ret)
{
	int	count_words;

	count_words = 0;
	count_words = ft_count_word(cur);
	ret = create_cmd(count_words);
	return (ret);
}

t_cmd	*ft_create_cmd_pipe(t_token *cur, t_cmd *ret)
{
	int	count_words;

	count_words = 0;
	count_words = ft_count_word(cur->next);
	ret = create_cmd(count_words);
	return (ret);
}

int	pipe_or_word(t_token *cur, t_cmd **ret, int i)
{
	if (cur->type == WORD)
		i = if_word_parser(cur, ret, i);
	else if (cur->type == PIPE)
		i = is_pipe(ret, cur, i);
	return (i);
}

int	is_pipe(t_cmd **ret, t_token *cur, int i)
{
	ft_lstadd_back_command(ret, ft_create_cmd_pipe(cur, (*ret)));
	i = 0;
	(*ret) = (*ret)->next;
	return (i);
}

int	if_word_parser(t_token *cur, t_cmd **ret, int i)
{
	(*ret)->cmd[i] = parse_string(cur->value, cur->len, (*ret)->cmd, i);
	i++;
	(*ret)->argc = i;
	return (i);
}
