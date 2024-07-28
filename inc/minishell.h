/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/28 12:52:22 by frankgar         ###   ########.fr       */
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
# include <sys/wait.h>
# include <ft_printf.h>
# include <sys/types.h>
# include <linux/limits.h>
# include <get_next_line.h>
# include <readline/readline.h>
# include <readline/history.h>

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

# define KEY    1
# define VALUE  2
# define NOT    "\0"

/* error messages */
# define MINI "\033[1;31mmini rush plus: \033[m"
# define ERR_MALLOC "error trying to allocate memory"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_ARGUMENT "too many arguments"

typedef struct s_command_lines	t_command_lines;
typedef struct s_minishell		t_minishell;
typedef struct s_get_line		t_get_line;
typedef struct s_token			t_token;
typedef struct s_env			t_env;

enum e_error_code
{
	MALLOC = 1,
	SYNTAX = 1 << 1,
	ARGUMENT = 1 << 2,
	PERROR = 1 << 3,
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
	R_HER = 1 << 8 | REDIR | R_IN,
	R_APP = 1 << 9 | REDIR | R_OUT,
	EXPAN = 1 << 10 | ARG,
	S_SHELL = 1 << 11,
	SYN_ERROR = 1 << 12,
	WILD_CARD = 1 << 13 | ARG,
};

typedef enum e_data_type
{
	T_TOKEN,
	T_ENV,
}	t_data_type;

struct s_command_lines
{
	int				status;
	char			**command_line;
	t_command_lines	*next;
};

struct s_env // array to array char **
{
	char	id[1];
	char	*key;
	char	*value;
	short	eql;
	t_env	*next;
};

struct s_minishell
{
	int				status;
	int				num_pipes;
	int				redir[2]; // para frank solo para el
	int				base_redir[2]; //de frank
	char			*get_line;
	t_env			*env;
	t_token			*token;
	t_command_lines	*cmd_lines;
};

struct s_token
{
	char				id[0];
	int					type;
	short				is_quote;
	char				*content;
	int					has_space;
	t_minishell			subs;
	t_token				*expand;
	t_token				*next;
	t_token				*prev;
};

/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

/*	built-ins/cd.c				*/
char	*get_pwd(void);

/*	built-ins/env.c				*/
t_env	*init_env(char **env);
int		_env(t_env *env, int num_commands);

/*  built-ins/unset.c */
int		_unset(t_env **env, char *key);

/*  built-ins/utils.c */
char	*search_env(t_env *env, char *key, int type);

/*	utils/clear_list.c			*/
int		clear_env(t_env **env);
int		clear_token(t_token **token);
int		clear_command_lines(t_command_lines **command_line);

/*	utils/errors.c				*/
char	*error_normalization(char *input);
int		error_msg(int error, int code_exit, char *input);

/*	utils/handler.list.c		*/
t_token	*cast_token(void *list);
t_env	*cast_env(void *list);
void	add_back(void **list, void *new, t_data_type size);
void	add_prev(void **list);

/*	utils/printf_list.c			*/
int		printf_env(t_env *env);
int		printf_token(t_token *token, char *col);
char	*printf_type(int type);

/*	parsing/add_token_type.c	*/
int		init_token(t_token **token, char *content, char *del, int space);
int		metacharacters(t_token **token, char *line, char *del, int *pos);
int		not_metacharacters(t_token **token, char *line, char *del, int *pos);
int		metacharacters_sub(t_token **token, char *line, int start, int end);
int		check_subshell(t_token **token, char *line, int *pos, int end);

/*	parsing/parsing.c			*/
int		parsing(t_minishell *mini);
/*	parsing/utils.c				*/
int		is_metacharacters(char c);
short	get_type(char *flag, char *content);
int		set_space(char *line, int *pos, char *del);
int		get_end_not_metacharacters(char *str);
int		get_end_token(char *str, char *del, int *pos, int size_del);
/*	parsing/syntax_err.c		*/
int		syntax_error(t_token **token);

/*	redirections/redir_heredoc.c	*/
int		is_heredoc(t_token *current, pid_t *redir, int *status);
/*	redirections/redir_in.c	*/
int		is_stdinp(t_token *current, int *redir, int *status);
/*	redirections/redir_out.c	*/
int		is_stdout(t_token *current, int *redir, int	*status);
/*	redirections/redirecctions.c	*/
int		parse_open(t_token *current, int type, int *redir);
#endif


/*
		Si encontramos $:    
							- La variable existe entre caracteres alfanumericos y '_'
							- El primer caracter ha de ser alfabetico y '_' (Si no es el caso, el token no se hace/expande, así que se mantiene el "$+contenido")
							- La cadena para hasta no encontrar un caracter válido y, si no está separado por un " " entonces va pegado
							- Aceptar "$?"

*/
