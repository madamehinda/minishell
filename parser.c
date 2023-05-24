/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:17:01 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/10 14:56:28 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

t_cmd	*create_cmd(int count_word)
{
	t_cmd	*cmd_line;

	cmd_line = malloc(sizeof(t_cmd) * 1);
	if (!cmd_line)
		return (NULL);
	cmd_line->cmd = NULL;
	cmd_line->cmd = malloc(sizeof(char *) * (count_word + 1));
	if (cmd_line->cmd == NULL)
		return (NULL);
	cmd_line->cmd[count_word] = NULL;
	cmd_line->next = NULL;
	cmd_line->heredoc_limit = NULL;
	cmd_line->here_doc = 0;
	cmd_line->fd_in = -1;
	cmd_line->fd_out = -1;
	cmd_line->status = 0;
	cmd_line->argc = 0;
	return (cmd_line);
}

static void	writing_here_doc(t_data *data, char *delimiter, int fd)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline("> ");
		if (g_exit_code == 130)
			break ;
		else if (!buffer)
		{
			ft_putstr_fd("here-document at line n delimited by end-of-file ",
				2);
			ft_putstr_fd("\n", 2);
			break ;
		}
		if (!ft_strcmp(delimiter, buffer))
			break ;
		if (ft_strchr(buffer, '$'))
			buffer = expand_heredoc(data, buffer);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	if (buffer)
		free(buffer);
}

static int	looking_for_heredoc(t_data *data, t_cmd *command)
{
	int		fd;
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = make_heredoc_name();
	fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	i = dup(fd);
	setup_signal_heredoc();
	writing_here_doc(data, command->heredoc_limit, i);
	close(i);
	i = open(tmp, O_RDONLY);
	close(fd);
	if (tmp)
	{
		unlink(tmp);
		free(tmp);
	}
	if (command->fd_in > 0)
		close(command->fd_in);
	command->fd_in = i;
	return (g_exit_code);
}

void	init_parse(int *i, t_cmd **ret, t_cmd **head, t_token **cur)
{
	(*i) = 0;
	(*ret) = NULL;
	(*ret) = ft_create_cmd((*cur), (*ret));
	(*head) = (*ret);
}

t_cmd	*parse_cmd_table(t_data *data, t_token *lexer)
{
	t_token	*cur;
	t_cmd	*ret;
	t_cmd	*head;
	int		i;

	i = 0;
	cur = lexer;
	init_parse(&i, &ret, &head, &cur);
	while (cur)
	{
		if (cur->type == PIPE || cur->type == WORD)
			i = pipe_or_word(cur, &ret, i);
		else if (is_redir_parse(cur) == TRUE)
			if_redir_parse(&cur, ret);
		if (cur->type == LIMITER)
		{
			ret->heredoc_limit = cur->value;
			ret->status = looking_for_heredoc(data, ret);
			if (g_exit_code == 130)
				ret->status = -1;
		}
		cur = cur->next;
	}
	return (ft_lstclear_token(&lexer), head);
}
