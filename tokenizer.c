/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 02:33:57 by hinda             #+#    #+#             */
/*   Updated: 2023/04/06 15:44:15 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	save_word(t_token **lexer, char *line, enum e_state status)
{
	int		i;
	t_token	*tok;

	i = 0;
	while (is_special_char(line, i) == FALSE)
	{
		i++;
	}
	tok = create_token(line, i, WORD, status);
	ft_lstadd_back_token(lexer, tok);
	return (i);
}

int	save_dquotes(t_token **lexer, char *line, enum e_state status)
{
	int		i;
	t_token	*tok;

	i = 0;
	while (line[i] && is_d_quotes(line, i) == FALSE)
	{
		i++;
	}
	tok = create_token(line, i, WORD, status);
	ft_lstadd_back_token(lexer, tok);
	return (i);
}

int	save_squotes(t_token **lexer, char *line, enum e_state status)
{
	int		i;
	t_token	*tok;

	i = 0;
	while (line[i] && is_s_quotes(line, i) == FALSE)
	{
		i++;
	}
	tok = create_token(line, i, WORD, status);
	ft_lstadd_back_token(lexer, tok);
	return (i);
}

int	save_redirection(t_token **lexer, char *line, int i, enum e_state status)
{
	int	j;

	j = i;
	if (is_special_char(line, i) == 2)
		ft_lstadd_back_token(lexer, create_token(line + (i++), 1, REDIR_OUT,
				status));
	else if (is_special_char(line, i) == 3)
		ft_lstadd_back_token(lexer, create_token(line + (i++), 1, REDIR_IN,
				status));
	else if (is_special_char(line, i) == 4)
	{
		ft_lstadd_back_token(lexer, create_token(line + (i++), 2, DREDIR_OUT,
				status));
		i++;
	}
	else if (is_special_char(line, i) == 5)
	{
		ft_lstadd_back_token(lexer, create_token(line + (i++), 2, HEREDOC,
				status));
		i++;
	}
	return (i - j);
}

int	tokenizer(t_token **lexer, char *line, int i, enum e_state status)
{
	(void)status;
	if (is_special_char(line, i) == 7)
	{
		i++;
		i += save_dquotes(lexer, line + i, DQUOTE);
		i++;
	}
	if (is_special_char(line, i) == FALSE)
		i += save_word(lexer, line + i, DEFAULT);
	else if (is_special_char(line, i) == 1)
		ft_lstadd_back_token(lexer, create_token(line + (i++), 1, PIPE,
				DEFAULT));
	else if (is_special_char(line, i) == 9)
		ft_lstadd_back_token(lexer, create_token(line + (i++), 1, WHITESPACE,
				DEFAULT));
	else if (is_special_char(line, i) > 1 && is_special_char(line, i) < 6)
		i += save_redirection(lexer, line, i, DEFAULT);
	else if (is_special_char(line, i) == 6)
	{
		i++;
		i += save_squotes(lexer, line + i, SQUOTE);
		i++;
	}
	return (i);
}
