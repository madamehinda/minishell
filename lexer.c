/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:43:24 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:33:00 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	is_special_char(char *line, int i)
{
	if (line[i] == '|')
		return (1);
	else if (line[i] == '>' && line[i + 1] != '>')
		return (2);
	else if (line[i] == '<' && line[i + 1] != '<')
		return (3);
	else if (line[i] == '>' && line[i + 1] == '>')
		return (4);
	else if (line[i] == '<' && line[i + 1] == '<')
		return (5);
	else if (line[i] == '\'')
		return (6);
	else if (line[i] == '\"')
		return (7);
	else if ((line[i] > 8 && line[i] < 14) || line[i] == 32)
		return (9);
	else if (line[i] == '\0')
		return (10);
	else
		return (0);
}

t_token	*read_input(char *line)
{
	int				i;
	t_token			*lexer;
	t_token			*final;
	enum e_state	status;

	i = 0;
	status = DEFAULT;
	lexer = NULL;
	final = NULL;
	while (line && line[i])
	{
		i = tokenizer(&lexer, line, i, status);
	}
	final = final_lexer(lexer);
	if_redir(final);
	free(line);
	ft_lstclear_token(&lexer);
	return (final);
}

void	if_redir(t_token *lexer)
{
	while (lexer && lexer->next)
	{
		if (lexer->type == REDIR_IN)
			lexer->next->type = STD_IN;
		else if (lexer->type == REDIR_OUT)
			lexer->next->type = TRUNC;
		else if (lexer->type == DREDIR_OUT)
			lexer->next->type = APPEND;
		else if (lexer->type == HEREDOC)
			lexer->next->type = LIMITER;
		lexer = lexer->next;
	}
}

char	*if_word(t_token **lexer, char **tmp)
{
	char	*str;

	str = NULL;
	while (*lexer && (*lexer)->type == WORD)
	{
		str = ft_strdup((*lexer)->value);
		*tmp = ft_strjoin_hinda(*tmp, str);
		if (str)
		{
			free(str);
			str = NULL;
		}
		*lexer = (*lexer)->next;
	}
	return (*tmp);
}

t_token	*final_lexer(t_token *lexer)
{
	char	*tmp;
	t_token	*final;

	final = NULL;
	tmp = NULL;
	while (lexer)
	{
		tmp = if_word(&lexer, &tmp);
		if (tmp)
		{
			ft_lstadd_back_token(&final, create_token(tmp, \
			ft_strlen(tmp), WORD, DEFAULT));
			free(tmp);
			tmp = NULL;
		}
		if (lexer && lexer->type == WHITESPACE)
			lexer = lexer->next;
		else if (lexer && lexer->type != WORD && lexer->type != WHITESPACE)
		{
			ft_lstadd_back_token(&final, create_token(lexer->value, lexer->len,
					lexer->type, DEFAULT));
			lexer = lexer->next;
		}
	}
	return (final);
}
