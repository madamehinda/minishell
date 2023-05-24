/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:51:36 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:42:07 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}

int	is_space(char *s)
{
	if ((*s == ' ') || (*s == '\t'))
		return (1);
	return (0);
}

int	is_space_2(char c)
{
	if ((c == ' ') || (c == '\t'))
		return (1);
	return (0);
}

int	check_open_quotes_expand(const char *line, int pos)
{
	int	open_dquotes;
	int	open_squotes;
	int	i;

	i = 0;
	open_dquotes = 0;
	open_squotes = 0;
	while (line[i] && i < pos)
	{
		if (line[i] == 34 && is_even(open_squotes))
			open_dquotes++;
		else if (line[i] == 39 && is_even(open_dquotes))
			open_squotes++;
		i++;
	}
	if (!is_even(open_squotes))
		return (0);
	return (1);
}

char	*parse_string(char *content, int len, char **argv, int i)
{
	int	j;

	j = 0;
	argv[i] = malloc(sizeof(char) * (len + 1));
	if (argv[i] == NULL)
		return (NULL);
	while (j < len && content[j] && argv)
	{
		argv[i][j] = content[j];
		j++;
	}
	argv[i][j] = '\0';
	return (argv[i]);
}
