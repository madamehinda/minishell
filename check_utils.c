/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:25:52 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:27:48 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	is_sep(char *line)
{
	if (*line == '|' || *line == '>' || *line == '<' || *line == '&')
		return (1);
	return (0);
}

int	is_sep_2(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int	begin_sep_error(char *line)
{
	while (*line && is_space(line))
		line++;
	if (*line == '|' || *line == ';')
		return (1);
	return (0);
}

int	end_sep_error(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
		i++;
	i--;
	while (line && i >= 0 && line[i] && is_space_2(line[i]))
		i--;
	if (line && i >= 0 && is_sep_2(line[i]))
		return (1);
	return (0);
}

int	ft_isalnum_mini(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}
