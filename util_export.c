/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 11:07:44 by imraoui           #+#    #+#             */
/*   Updated: 2023/04/06 15:46:44 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strdup_plus(char *str)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[j] && str[j] != '+')
	{
		dest[i] = str[j];
		i++;
		j++;
	}
	if (str[j] == '+')
	{
		j++;
		while (str[j])
		{
			dest[i] = str[j];
			i++;
			j++;
		}
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_select2(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '+' && str[i] != '=')
	{
		dest[j] = str[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*util_ft_select(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	dest = NULL;
	while (str && str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		dest = (char *)malloc(sizeof(char) * (i + 2));
	else if (str[i] == '\0')
		dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	return (dest);
}

char	*ft_select(char *str)
{
	char	*dest;
	int		j;

	j = 0;
	dest = util_ft_select(str);
	while (str[j] && str[j] != '=' && str[j] != '+')
	{
		dest[j] = str[j];
		j++;
	}
	if (str[j] == '+' && str[j + 1] == '=')
	{
		dest[j++] = '=';
		dest[j--] = '\0';
	}
	else if (str[j] == '=')
	{
		dest[j++] = '=';
		dest[j] = '\0';
	}
	else
		dest[j] = '\0';
	return (dest);
}

char	*ft_select1(char *str)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '=')
		dest = (char *)malloc(sizeof(char) * (strlen(str) - i + 1));
	if (!dest)
		return (NULL);
	i++;
	while (str && str[i])
	{
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}
