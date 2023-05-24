/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:08:51 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 17:16:19 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	check_open_quotes(const char *line)
{
	int	open_dquotes;
	int	open_squotes;

	open_dquotes = 0;
	open_squotes = 0;
	while (*line)
	{
		if (*line == 34 && is_even(open_squotes))
			open_dquotes++;
		else if (*line == 39 && is_even(open_dquotes))
			open_squotes++;
		line++;
	}
	if (!is_even(open_dquotes) || !is_even(open_squotes))
		return (1);
	return (0);
}

int	open_quotes(const char *line, int pos)
{
	int	open_dquotes;
	int	open_squotes;
	int	i;

	i = 0;
	open_dquotes = 0;
	open_squotes = 0;
	while (i < pos)
	{
		if (line[i] == 34 && is_even(open_squotes))
			open_dquotes++;
		else if (line[i] == 39 && is_even(open_dquotes))
			open_squotes++;
		i++;
	}
	if (!is_even(open_dquotes) || !is_even(open_squotes))
		return (1);
	return (0);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
