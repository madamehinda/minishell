/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 00:12:33 by hinda             #+#    #+#             */
/*   Updated: 2023/04/05 10:24:32 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

char	*str_ndup(char *str, unsigned int start, unsigned int end)
{
	char			*duped;
	unsigned int	len;
	int				i;

	i = 0;
	len = end - start;
	duped = NULL;
	duped = malloc(sizeof(char) * (len + 1));
	while (start < end)
	{
		duped[i++] = str[start++];
	}
	duped[i] = 0;
	return (duped);
}

int	is_d_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		return (1);
	}
	return (0);
}

int	is_s_quotes(char *line, int i)
{
	if (line[i] == '\'')
	{
		return (1);
	}
	return (0);
}

void	msg_error1(char *err)
{
	perror(err);
}

void	msg_error(char *err)
{
	perror(err);
	exit(1);
}
