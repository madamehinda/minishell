/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:26 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 13:04:55 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_strings(char *line, int i, char *new)
{
	char	*str;

	str = NULL;
	str = ft_strdup_char(line[i]);
	new = ft_strjoin_hinda(new, str);
	free(str);
	str = NULL;
	return (new);
}

int	exit_code(int i, char **new)
{
	char	*str;

	str = NULL;
	str = ft_itoa(g_exit_code);
	*new = ft_strjoin_hinda(*new, str);
	free(str);
	str = NULL;
	return (i += 2);
}

int	if_dollar(t_data *data, char *line, int i, char **new)
{
	int		start;
	int		end;
	char	*str;
	char	*env;

	env = NULL;
	start = i;
	while (ft_isalnum_mini(line[i]) && line[i])
		i++;
	end = i;
	str = env_finder(line, start, end);
	env = check_var(str, data);
	free(str);
	if (env)
	{
		env = ft_select1(env);
		*new = ft_strjoin_hinda(*new, env);
		free(env);
		env = NULL;
	}
	return (i);
}

char	*get_var_echo(char *str)
{
	char	*dest;
	int		i;
	int		j;
	int		start;
	int		end;

	i = 0;
	j = 0;
	if (str[i] == '$')
		i++;
	start = i;
	while (str[i] && ft_isalnum_mini(str[i]))
		i++;
	end = i;
	dest = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!dest)
		return (NULL);
	while (start < end && ft_isalnum_mini(str[start]))
	{
		dest[j] = str[start];
		j++;
		start++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*check_var(char *str, t_data *mini)
{
	int		i;
	char	*var;

	i = 0;
	var = NULL;
	var = ft_select2(mini->env[i]);
	while ((mini->env[i]) && ft_strncmp(mini->env[i], str, ft_strlen(str)))
		i++;
	if (mini->env[i] == 0)
		return (free(var), NULL);
	else
		return (free(var), mini->env[i]);
}
