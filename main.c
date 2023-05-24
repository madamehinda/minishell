/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:50:28 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/06 15:39:31 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include "minishell.h"

char	*display_prompt(t_data *data)
{
	static char	*prompt;

	prompt = NULL;
	if (prompt)
	{
		free(prompt);
		prompt = NULL;
	}
	prompt = readline("🐚> ");
	if (!prompt)
	{
		ft_free(data->env);
		printf("BYE BYE 😘\n");
		exit(0);
	}
	if (ft_strlen(prompt) == 0)
		prompt = display_prompt(data);
	if (ft_strlen(prompt) > 0)
		add_history(prompt);
	return (prompt);
}

int	check_input(t_data *data)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(data->line);
	if (ft_strlen(tmp) > MAXLINE)
	{
		g_exit_code = 2;
		printf(BOLD_YELLOW "Command line is too long\n " RESET);
		printf(BOLD_YELLOW "You want to break the parsing or what?\n" RESET);
		return (free(tmp), g_exit_code);
	}
	if (check_open_quotes(tmp) == TRUE)
	{
		g_exit_code = 2;
		printf(BOLD_YELLOW "error: check your quotes!\n" RESET);
		return (free(tmp), g_exit_code);
	}
	if (tmp && ((begin_sep_error(tmp) == TRUE) || end_sep_error(tmp) == TRUE))
	{
		g_exit_code = 2;
		printf("syntax error\n");
		return (free(tmp), g_exit_code);
	}
	return (free(tmp), 1);
}

int	is_forbidden(t_data *data)
{
	char	*line;

	line = NULL;
	line = ft_strdup(data->line);
	if (is_ascii(line) == FALSE)
	{
		printf("error: invalid characters found");
		return (free(line), 2);
	}
	if (forbidden_series(line) > 0)
	{
		if (forbidden_series(line) == 1)
		{
			g_exit_code = 2;
			printf("syntax error near unexpected token\n");
			return (free(line), g_exit_code);
		}
		else if (forbidden_series(line) == 2)
		{
			printf("tout ce qui n'est pas demande n'est pas a faire\n");
			return (free(line), 2);
		}
	}
	return (free(line), 1);
}

void	clear_main(t_data *data)
{
	ft_lstclear_command(&data->cmds);
	if (data->nbr_pipe > 0)
		free_pfd(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argv;
	if (argc == 1)
	{
		if (init_struct(&data, env) == FALSE)
			return (1);
		while (1)
		{
			set_signal(SHE, IGN);
			data.line = display_prompt(&data);
			if (check_input(&data) != 2 && is_forbidden(&data) != 2)
			{
				ft_init_mini(&data);
				exec_cmd(data.cmds, &data);
				ft_close_fd(data.cmds);
				clear_main(&data);
			}
		}
		ft_close(&data, data.cmds);
		ft_free_mini(data.cmds, &data);
	}
	else
		printf("error, too much arguments\n");
	return (0);
}
