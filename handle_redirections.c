/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:49:36 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 14:33:21 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

int	handle_input(t_cmd *cmd_line, char *filename)
{
	int	fd_in;

	if (cmd_line->fd_in > 0)
		close(cmd_line->fd_in);
	fd_in = open(filename, O_RDONLY);
	if (fd_in < 0)
	{
		printf("%s : %s\n", filename, strerror(errno));
		cmd_line->fd_in = -1;
		return (-1);
	}
	cmd_line->fd_in = fd_in;
	return (0);
}

int	handle_output_simple(t_cmd *cmd_line, char *filename)
{
	int	fd_out;

	fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out < 0)
	{
		printf("%s : %s\n", filename, strerror(errno));
		cmd_line->fd_out = -1;
		return (-1);
	}
	if (cmd_line->fd_out > 0)
		close(cmd_line->fd_out);
	cmd_line->fd_out = fd_out;
	return (0);
}

int	handle_output_double(t_cmd *cmd_line, char *filename)
{
	int	fd_out;

	fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd_out < 0)
	{
		printf("%s : %s\n", filename, strerror(errno));
		return (1);
	}
	if (cmd_line->fd_out > 0)
		close(cmd_line->fd_out);
	cmd_line->fd_out = fd_out;
	return (0);
}
