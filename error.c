/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:31:07 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 09:31:20 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	is_ascii(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isascii(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	forbidden_series(char *s)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s[i])
	{
		flag = open_quotes(s, i);
		if (s[i] == ';' && s[i + 1] == ';' && !flag)
			return (1);
		else if (s[i] == '|' && s[i + 1] == ';' && !flag)
			return (1);
		else if (s[i] == '&' && s[i + 1] == ';' && !flag)
			return (1);
		else if (s[i] == ';' && s[i + 1] == '&' && !flag)
			return (1);
		else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>' && !flag)
			return (1);
		i++;
	}
	return (0);
}
