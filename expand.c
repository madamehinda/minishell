/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:46:37 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/10 14:44:35 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

char	*ft_strdup_char(char c)
{
	char	*dest;

	dest = malloc(sizeof(char) * 2);
	dest[0] = c;
	dest[1] = '\0';
	return (dest);
}

char	*env_finder(char *line, int start, int end)
{
	int		i;
	char	*str;
	char	*dup;

	i = 0;
	str = NULL;
	dup = ft_strdup(line);
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	str[(end - start)] = '\0';
	while (start < end)
	{
		str[i] = dup[start];
		i++;
		start++;
	}
	free(dup);
	return (str);
}

int	ft_dollar(char *s, int i, char **new)
{
	if (s[i] && check_open_quotes_expand(s, i) && ft_isalnum_mini(s[i + 1]))
		return (1);
	else if (s[i] && check_open_quotes_expand(s, i) && ((is_d_quotes(s, i + 1)
				|| (is_s_quotes(s, i + 1)))))
		return (0);
	else if (s[i] && (!check_open_quotes_expand(s, i) || !ft_isalnum_mini(s[i
					+ 1])))
		*new = join_strings(s, i, *new);
	return (0);
}

int	check_break(char *line, int *i, char **new, int *dollar)
{
	int	flag_break ;

	flag_break = 0;
	if (line[*i] == '$' && line)
	{
		if (check_open_quotes_expand(line, *i) && line[*i] == '$' && line[*i
				+ 1] == '?')
		{
			*i = exit_code(*i, new);
			flag_break = 1;
		}
		*dollar = ft_dollar(line, *i, new);
		if (line[*i])
			(*i)++;
	}
	return (flag_break);
}

char	*replace(t_data *data)
{
	int		dollar;
	int		i;
	char	*new;

	i = 0;
	dollar = 0;
	new = NULL;
	while (data->line[i])
	{
		if (check_break(data->line, &i, &new, &dollar) == 1)
			break ;
		if (dollar == 1)
			i = if_dollar(data, data->line, i, &new);
		if (data->line[i] != '$' && data->line[i])
			new = join_strings(data->line, i, new);
		dollar = 0;
		if (data->line[i] != '$' && data->line[i])
			i++;
	}
	data->line = ft_strdup(new);
	return (free(new), data->line);
}
