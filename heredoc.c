/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:26:43 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/05 09:51:12 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

char	*make_heredoc_name(void)
{
	static int	i;
	char		*name;
	char		*number;

	name = NULL;
	name = ft_strdup(".tmp.minishell.heredoc");
	number = ft_itoa(i);
	if (!number)
		return (NULL);
	name = ft_strjoin_hinda(name, number);
	free(number);
	i++;
	return (name);
}

int	ft_dollar_heredoc(char *s, int i, char **new)
{
	if (s[i] && ft_isalnum_mini(s[i + 1]))
		return (1);
	else
		*new = join_strings(s, i, *new);
	return (0);
}

int	check_dollar_heredoc(char *line, int *i, char **new, int dollar)
{
	while (line[*i] == '$' && line[*i])
	{
		dollar = ft_dollar_heredoc(line, *i, new);
		(*i)++;
	}
	return (dollar);
}

char	*expand_heredoc(t_data *data, char *buffer)
{
	int		dollar;
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (buffer[i])
	{
		dollar = check_dollar_heredoc(buffer, &i, &new, dollar);
		if (dollar == 1)
			i = if_dollar(data, buffer, i, &new);
		new = join_strings(buffer, i, new);
		dollar = 0;
		if (buffer[i] != '$' && buffer[i])
			i++;
	}
	buffer = ft_strdup(new);
	return (free(new), buffer);
}
