/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <imraoui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:51:07 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/10 14:56:55 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include "style.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//hinda

# define TRUE 1
# define FALSE 0

# define MAXLINE 1024
# define MAXARGS 128 // maxargs in struct can't be variable

# define PATH_MAX 4096
# define SHE 10
# define HER 11
# define IGN 12
# define SINGLE "\'"
# define DOUBLE "\""
# define HEREDOC_PREFIX ".tmp.minishell.heredoc"
//imen
# define ERR_INFILE "Infile"
# define ERR_HERDOC "herdoc"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe Failed"
# define ERR_FORK "fork failed\n"

extern int			g_exit_code;

enum				e_state
{
	DEFAULT,
	SQUOTE,
	DQUOTE,
};

enum				e_type
{
	WORD,
	WHITESPACE,
	NEW_LINE,
	PIPE,
	HEREDOC,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	DREDIR_OUT,
	S_QUOTE,
	D_QUOTE,
	STD_IN,
	TRUNC,
	APPEND,
	LIMITER,
	END_OF_LINE
};

//TOKENS

typedef struct s_token
{
	char			*value;
	int				len;
	int				status;
	enum e_type		type;
	enum e_state	qstatus;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_expand
{
	int				dollar;
	int				i;
	char			*new;
}					t_expand;

typedef struct s_cmd
{
	char			**cmd;
	char			*heredoc_limit;
	int				status;
	int				fd_in;
	int				fd_out;
	int				here_doc;
	int				argc;
	pid_t			pid;
	pid_t			pid_one;
	struct s_cmd	*next;

}					t_cmd;

typedef struct s_data
{
	char			*line;
	char			**env;
	int				**pfd;
	t_cmd			*cmds;
	int				nbr_cmd;
	int				nbr_pipe;
	t_token			*token;
	t_expand		*expand;
	int				exit_status;
}					t_data;

/*init.c*/

int					init_struct(t_data *data, char **env);

/*free.c*/

void				free_array(char **array);

/*parser.c*/

int					valid_syntax(char *line);
int					forbidden_series(char *s);

/*lexer_utils.c*/

int					is_ascii(char *s);
t_token				*create_token(char *value, int len, enum e_type type,
						enum e_state status);
void				ft_lstadd_back_token(t_token **lst, t_token *new);
//void				push(t_token **head_ref, t_token *new);
void				print_liste(t_token *head);
int					is_special_char(char *line, int i);
void				if_redir(t_token *lexer);
t_token				*read_input(char *line);
void				print_token(t_token **head);
int					is_sep(char *line);
t_cmd				*parse_cmd_table(t_data *data, t_token *lexer);
void				ft_lstadd_back_command(t_cmd **lst, t_cmd *new);
int					ft_count_word(t_token *lexer);
void				redefine_status(t_token *lexer);
int					ft_count_list(t_cmd *cur);
int					is_s_quotes(char *line, int i);
t_token				*final_lexer(t_token *lexer);
void				ft_init_mini(t_data *data);

int					check_open_quotes(const char *line);
int					check_open_quotes_expand(const char *line, int pos);
int					open_quotes(const char *line, int pos);
int					begin_sep_error(char *line);
int					end_sep_error(char *line);
char				*parse_quotes(t_token *lexer);
int					save_dquotes(t_token **lexer, char *line,
						enum e_state status);
void				sig_handler(int signum);
void				free_check_input(char *s1, char *s2);
char				*display_prompt(t_data *data);
void				ft_basic_functions(char *line, char **argv);
int					is_even(int num);
int					ft_quotes(char *s);
void				display_env(char **env);
int					is_space(char *line);
char				*ft_strcpy(char *dest, char *src);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlen_mat(char **tab);
int					ft_isalnum_mini(int c);
void				print_simple(char *str);
char				*replace(t_data *data);
char				*join_strings(char *line, int i, char *new);
int					if_dollar(t_data *data, char *line, int i, char **new);
int					exit_code(int i, char **new);
int					expand_finder(char *str);
char				*env_finder(char *line, int start, int end);
int					count_nodes(t_cmd *cmd_table);
char				*ft_strdup_char(char c);
void				print_liste_cmd(t_cmd **head);
;
int					is_d_quotes(char *line, int i);
char				*str_ndup(char *str, unsigned int start, unsigned int end);
char				*make_heredoc_name(void);
int					tokenizer(t_token **lexer, char *line, int i,
						enum e_state status);
void				set_signal(int sig_int, int sig_quit);
int					handle_output_double(t_cmd *cmd_line, char *filename);
int					handle_output_simple(t_cmd *cmd_line, char *filename);
int					handle_input(t_cmd *cmd_line, char *filename);
void				delete_tokens(t_token *head);
int					is_d_quotes(char *line, int i);
int					is_s_quotes(char *line, int i);
char				*parse_string(char *content, int len, char **argv, int i);
int					ft_count_word(t_token *lexer);
t_cmd				*ft_create_cmd(t_token *cur, t_cmd *ret);
void				if_stdin(t_token **cur, t_cmd *ret);
void				if_trunc(t_token **cur, t_cmd *ret);
void				if_append(t_token **cur, t_cmd *ret);
void				setup_signal_heredoc(void);
t_cmd				*create_cmd(int count_word);
int					is_redir_parse(t_token *cur);
void				if_redir_parse(t_token **cur, t_cmd *ret);
int					is_pipe(t_cmd **ret, t_token *cur, int i);
int					if_word_parser(t_token *cur, t_cmd **ret, int i);
int					pipe_or_word(t_token *cur, t_cmd **ret, int i);
char				*expand_heredoc(t_data *data, char *buffer);
void				ft_lstclear_token(t_token **lst);
int					verif_one(t_cmd *cmd_exec, t_data *data);

//bullting
void				realloc_env(t_data *mini, char *str);
int					ft_env(t_data *mini);
void				get_env(t_data *mini, t_cmd *cmd, char **argv);
int					print_export(t_data *mini);
int					ft_echo(char **argv, t_data *mini, t_cmd *exec_cmd);
int					ft_check(char *argv);
char				*ft_get_add_env(t_data *mini, char *str);
void				ft_export(char **argv, t_data *mini, t_cmd *exec_cmd);
void				ft_free(char **str);
int					is_plus(char *str);
int					is_export(char *str);
char				*strdup_plus(char *str);
char				*ft_select(char *str);
char				*ft_select1(char *str);
char				*ft_select2(char *str);
void				realloc_env_be(t_data *mini, char *str);
void				realloc_unset(t_data *mini, char *str);
void				ft_unset(t_data *mini, t_cmd *cmd, char **argv);
void				ft_pwd(void);
int					get_var(char *var, char **env);
int					strjoint_env(char *var, char *path, t_data *mini);
char				*get_home(t_data *mini, char *var);
int					cd_new_path(char **cmd, int i, t_data *mini, char *newpath);
int					ft_cd(char **cmd, t_data *mini);
int					is_exit(char *str);
void				ft_many_arg(t_data *mini, t_cmd *cmd);
void				ft_exit(t_data *mini, char **cmd, t_cmd *exec_cmd);
int					is_builtin(t_data *mini, char **argv, t_cmd *exec_cmd);
int					builtin_env(char **argv);
void				util_unset(t_data *mini, int i, int j, char **temp);
char				*get_var_echo(char *str);
char				*get_val_echo(char *str);
char				*check_var(char *str, t_data *mini);
char				*get_val_echo_space(char *str);
int					ft_print_var_quote(char *str, t_data *mini);
int					ft_print_var_sans_quote(char *str, t_data *mini);
void				ft_exit_pipe(t_data *mini, char **cmd, t_cmd *exec_cmd,
						t_cmd *head);

//  execution
void				ft_close_fd(t_cmd *cmd_exec);
void				ft_close(t_data *data, t_cmd *cmd_exec);
void				close_fd(t_data *data, t_cmd *cmd_exec);
void				exec_cmd(t_cmd *exec_cmd, t_data *data);
void				open_file(t_data *data, t_cmd *cmd_exec, int i);
void				exec_one_cmd(t_cmd *cmd_exec, t_data *data);
void				exec_pipe(t_cmd *cmd_exec, t_data *data, t_cmd *head);
void				free_pfd(t_data *data);
void				creat_pipes(t_data *data);
void				free_exeve(t_data *data, t_cmd *cmd_exec);
void				free_exeve_one(t_data *data, t_cmd *cmd_exec);
int					verif(t_cmd *cmd_exec, t_data *data);
int					child(t_cmd *cmd_exec, t_data *data, t_cmd *head);
void				msg_error1(char *err);
void				msg_error(char *err);
int					msg(char *err);
void				err_msg(char *cmd, char *msg);
int					ft_no_path(char **env);
char				**ft_get_path(char **env);
char				*get_cmd(char *cmd, char **envp);
void				msg_error(char *err);
void				ft_close_pipe(t_data *data, t_cmd *cmd_exec);
void				fct_exeve(t_cmd *cmd_exec, t_data *data);
void				father(int status);
int					is_builtin_pipe(t_data *mini, char **argv, t_cmd *exec_cmd,
						t_cmd *head);
void				ft_many_arg_pipe(t_data *mini, t_cmd *cmd, t_cmd *head);
// redir
void				redir_builltin(t_cmd *exec_cmd, t_data *data);
void				redir_one_cmd(t_cmd *cmd_exec);
void				redir_begin(t_data *data, t_cmd *cmd_exec, int i);
void				redir_middle(t_data *data, t_cmd *cmd_exec, int i);
void				redir_end(t_data *data, t_cmd *cmd_exec, int i);
//free minishell
void				ft_free_mini(t_cmd *exec_cmd, t_data *data);
void				ft_free(char **str);
void				ft_lstdelone_token(t_token *lst);
void				ft_lstclear_token(t_token **lst);
void				ft_lstclear_command(t_cmd **lst);
void				ft_lstdelone_command(t_cmd *lst);
void				ft_lstclear_command(t_cmd **lst);
void				ft_free_exit(t_cmd *exec_cmd, t_data *data);
void				ft_free_exit_pipe(t_cmd *exec_cmd, t_data *data);
//signal_exec
void				signal_nl(int num);
void				child_signal(int num);
void				hd_sig_child(int num);
void				hd_sig_parent(int num);
void				signal_fork(void);
int					is_space_2(char c);
void				sig_init(int sig);
#endif
