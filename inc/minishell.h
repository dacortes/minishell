/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/20 13:35:37 by frankgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <ft_printf.h>
# include <linux/limits.h>
# include <get_next_line.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

/******************************************************************************/
/*                            COLORS                                          */
/******************************************************************************/

# define END	"\033[m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[1;34m"
# define TUR	"\033[1;35m"
# define CYAN	"\033[1;36m"
# define ORANGE	"\033[38;5;208m"
# define PURPLE	"\033[38;5;128m"

/******************************************************************************/
/*                            STRUCTURES                                      */
/******************************************************************************/

# define DOUBLE_QUOTES  34
# define SIMP_QUOTES    39
# define WILDCARD       42

# define TRUE       1
# define FALSE      0
# define ERROR      -1
# define FOUND      0
# define NOT_FOUND  -1
# define CHILD		0
# define NO_CHILD	1

# define KEY    1
# define VALUE  2
# define NOT    "\0"

/* error messages */
# define MINI "\033[1;31mmini rush plus: \033[m"
# define ERR_MALLOC "%serror trying to allocate memory `%s'\n"
# define ERR_SYNTAX "%ssyntax error near unexpected token `%s'\n"
# define ERR_ARGUMENT "%stoo many arguments `%s'\n"
# define ERR_EXPORT "%sexport: not a valid identifier `%s'\n"
# define ERR_AMBIGUOUS "%s%s: ambiguous redirection%s\n"
# define ERR_NO_FOUND "%s%s: command not found\n"
# define ERR_IS_DIR "%s%s: Is a directory\n"
# define ERR_NUMERIC "%s%s: numeric argument required\n"

typedef struct s_minishell		t_minishell;
typedef struct s_token			t_token;
typedef struct s_env			t_env;
typedef struct s_basic			t_basic;
typedef union u_content			t_content;
typedef union u_data_type		t_data_type;

enum e_error_code
{
	MALLOC = 1,
	SYNTAX = 1 << 1,
	ARGUMENT = 1 << 2,
	PERROR = 1 << 3,
	EXPORT = 1 << 4,
	EXIT = 1 << 5,
	AMBIGUOUS = 1 << 6,
	NO_FOUND = 1 << 7,
	IS_DIR = 1 << 8,
	NUMERIC_ARG = 1 << 9,
};

enum e_tokens_types
{
	L_OPERAND = 1,
	OR = 1 << 1 | L_OPERAND,
	AND = 1 << 2 | L_OPERAND,
	ARG = 1 << 3,
	PIPE = 1 << 4,
	REDIR = 1 << 5,
	R_IN = 1 << 6 | REDIR,
	R_OUT = 1 << 7 | REDIR,
	R_HER = 1 << 8 | R_IN,
	R_APP = 1 << 9 | R_OUT,
	EXPAN = 1 << 10 | ARG,
	S_SHELL = 1 << 11,
	SYN_ERROR = 1 << 12,
	WILD_CARD = 1 << 13 | EXPAN,
	SUBS_SYN_ERR = S_SHELL | SYN_ERROR,
};

typedef enum e_data_enum
{
	T_TOKEN,
	T_ENV,
}	t_data_enum;

struct s_env
{
	char	*key;
	char	*value;
	short	eql;
};

struct s_minishell
{
	int		status;
	int		prev_status;
	char	*user;
	int		term_fd[2];
	int		redir[2];
	char	*get_line;
	char	*cur_dir;
	char	*old_dir;
	t_basic	*env;
	t_basic	*token;
};

union u_content
{
	t_minishell	*subs;
	int			redir_here[2];
};

struct s_token
{
	int			type;
	short		is_quote;
	short		expanded;
	int			has_space;
	char		*content;
	t_content	token_content;
};

union u_data_type
{
	t_token	*token;
	t_env	*env;
};

struct s_basic
{
	t_data_type		data;
	t_basic			*next;
	t_basic			*prev;
};

/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

/*	built-ins/builtins.c		*/
int		is_builtin(t_basic *start, t_basic *end);
int		do_builtin(t_minishell *mini, char **cmd);

/*	built-ins/cd.c				*/
int		replace(t_basic **env, char	*key, char *value);
char	*get_pwd(void);
int		update_oldpwd(t_minishell *mini, char *dir);
int		_cd(t_minishell *mini, char **command, int num_arg);

/*	built-ins/echo.c				*/
int		_echo(char **command, int num_arg);

/*	built-ins/env.c				*/
t_basic	*init_env(char **env);
int		add_env(t_basic **new_env, char *line);
int		_env(t_basic *list, int num_arg);

/*	built-ins/exit.c				*/
int		_exit_(t_minishell *mini, char **command, int num_arg);

/*	built-ins/export.c			*/
int		add_export(t_basic **env, char *line);
int		export_loop(t_basic **env, char **command);
int		_export(t_basic *env);

/*	built-ins/pwd.c			*/
int		_pwd(void);

/*	built-ins/unset.c				*/
int		_unset(t_basic **env, char *key);
int		unset_loop(t_basic **env, char **command, int num_arg);

/*  built-ins/utils_env.c 			*/
int		is_metacharacters(char c);
void	printf_env(void *content);
char	*is_shlvl(char *key, char *value);
int		key_compare(t_data_type *data, void *key);
char	*search_env(t_basic *env, char *key, int type);

/*  built-ins/utils_env.c 			*/
void	printf_export(void *content);

/*	manager/manager_actions.c		*/
pid_t	_subshell(t_minishell *mini, t_basic *start, t_basic *end);
pid_t	_builtin(t_minishell *mini, t_basic *start, t_basic *end, int is_child);
void	_execute(t_minishell *mini, t_basic *start, t_basic *end);
pid_t	_child_builtin(
			t_minishell *mini, t_basic *start, t_basic *end, char **cmd);
pid_t	_execute_no_child(
			t_minishell *mini, t_basic *start, t_basic *end);

/*	manager/manager_sets.c			*/
int		set_child(int mod_flag, int value);
void	set_skip(t_minishell *mini, t_basic *end, int	*skip);

/*	manager/manager_utils.c			*/
char	*get_path(t_minishell *mini, char *cmd);
char	*select_cmd_path(char **path, char *cmd);
char	**substract_env(t_minishell *mini);
int		get_env_size(t_basic *env);

/*	manager/manager.c			*/
void	manager(t_minishell *mini);

/*	expansion/dollar.c			*/
char	*expansion(t_minishell *mini, char *content);

/*	expansion/token.c			*/
int		expand_token(t_minishell *mini, t_basic **start, t_basic *end);

/*	expansion/union_token		*/
t_basic	*union_token(t_basic *start, t_basic *end);

/*	expansion/utils.c			*/
int		is_space(char c);
int		get_end_space(char *str);
int		split_space(t_basic **token, char *line, char *del, int *pos);
int		search_node(void *src, void *node);

/*  expansion/wild_card.c       */
t_basic	*expand_wild_cards(t_basic *token);

/*	parsing/add_token.c			*/
int		get_token_content(t_content *token_content, char *content, int type);
t_token	*new_token(char *content, char *del, int space);
int		init_token(t_basic **token, char *content, char *del, int space);

/*	parsing/metacharacters.c	*/
int		metacharacters(t_basic **token, char *line, char *del, int *pos);
int		not_metacharacters(t_basic **token, char *line, char *del, int *pos);
int		metacharacters_sub(t_basic **token, char *line, int start, int end);
int		check_subshell(t_basic **token, char *line, int *pos, int end);

/*	parsing/parsing.c			*/
int		parsing(t_minishell *mini);
int		syntax_error(t_basic **content);

/*  redirections/redir_append.c */
int		_append(t_minishell *mini, t_basic *current);

/*	redirections/redir_heredoc.c	*/
int		open_heredoc(t_minishell *mini, t_basic *current, int *redir);
int		_heredoc(t_minishell *mini, t_basic *current);
void	close_heredocs(t_minishell *mini);
int		do_heredoc(t_minishell *mini);

/*  redirections/redir_in.c */
int		_stdinp(t_minishell *mini, t_basic *current);

/*  redirections/redir_out.c */
int		_stdout(t_minishell *mini, t_basic *current);

/*  redirections/redirections.c */
int		redirections(t_minishell *mini, t_basic *start, t_basic *end);
int		reset_redirs(t_minishell *mini);
int		parse_open(t_basic *current);

/*	parsing/utils.c				*/
short	get_type(char *flag, char *content);
int		set_space(char *line, int *pos, char *del);
int		get_end_not_metacharacters(char *str);
int		get_end_token(char *str, char *del, int *pos, int size_del);

/*	parsing/syntax_utils.c				*/
int		set_syntax_error(t_token *token, t_basic *iter);

/*  signals/heredoc_signals     */
int		get_break_it(int flag, int value);
void	break_it(int signal);

/*	prompt/prompt.c				*/
char	*ft_strjoin_max(char **need);
char	*get_dir_branch(void);
char	*get_branch(void);
int		prompt(t_minishell *mini);

/*	signals/signals.c		*/
int		get_status(int flag, int value);
void	term_init(void);
void	_sigint(int sig);
void	handle_siginth(int sig);
void	handle_signaled(int *status, int signal);

/*	utils/errors.c			*/
int		error_msg(int error, int code_exit, char *input);
void	*protected(void *memory, char *error_str);

/*	utils/clear_list.c			*/
char	*free_double_ptr(char **ptr);
void	free_env(void *content);
void	free_token(void *content);
void	free_minishell(t_minishell *mini, int flag);
void	free_list(t_basic *node, void (*f)(void *));

/*	utils/handler.list.c		*/
void	*get_last(t_basic *list);
void	add_prev(t_basic **list, int flag);
void	add_back(t_basic **list, t_basic *new);

/*	utils/loops.c				*/
int		content_loop(t_basic *node, void (*f)(void *));
t_basic	*bool_loop(t_basic *node, int (*cmp)(t_data_type *, void *), void *arg);
t_basic	*bool_loop_void(t_basic *node, int (*cmp)(void *, void *), void *arg);

/*	utils/printf_list.c 		*/
char	*printf_type(int type);
void	printf_content_token(void *content);
void	printf_token(t_basic *token);

/*	utils/get_cmds.c			*/
char	**get_cmds(t_basic *start, t_basic *end);
#endif
