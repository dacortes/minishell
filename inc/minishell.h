/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/08/01 09:57:18 by codespace        ###   ########.fr       */
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

typedef struct s_minishell		t_minishell;
typedef struct s_token			t_token;
typedef struct s_env			t_env;

typedef	struct s_basic_list		t_basic_list;
typedef union  u_content		t_content;
typedef	union  u_type_list		t_type_list;


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
	WILD_CARD = 1 << 13 | EXPAN,
};

typedef enum e_data_type
{
	T_TOKEN,
	T_ENV,
}	t_data_type;

struct s_env // array to array char **
{
	char	*key;
	char	*value;
	short	eql;
};

struct s_minishell
{
	int				status;
	char			*get_line;
	t_basic_list	*env;
	t_basic_list	*token;
};

union u_content
{
	t_minishell		*subs;
	t_basic_list	*expand;
	int			redir_here[2];
};

struct s_token
{
	int			type;
	short		is_quote;
	int			has_space;
	char		*content;
	t_content	token_content;
};


union u_type_list
{
	t_token	*token;
	t_env	*env;
};


struct s_basic_list
{
	t_type_list		list_content;
	t_basic_list	*next;
	t_basic_list	*prev;
};

/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

int		iter_list_list_content(t_basic_list *node, void (*f)(void *));

/*	built-ins/cd.c				*/
char	*get_pwd(void);

/*	built-ins/env.c				*/
t_basic_list *init_env(char **env);
int		_env(t_basic_list *list, int num_commands);

/*  built-ins/utils.c */
void	printf_env(void *content);
char	*is_shlvl(char *key, char *value);

int 	parsing(t_minishell *mini);

short	get_type(char *flag, char *content);
int		set_space(char *line, int *pos, char *del);
int		get_end_not_metacharacters(char *str);
int		get_end_token(char *str, char *del, int *pos, int size_del);

int	error_msg(int error, int code_exit, char *input);

int	metacharacters(t_basic_list **token, char *line, char *del, int *pos);
int	not_metacharacters(t_basic_list **token, char *line, char *del, int *pos);




char	*printf_type(int type);



/*	utils/clear_list.c			*/
void 	free_env(void *content);
void	free_token(void *content);
void	free_minishell(t_minishell *mini, int flag);
void 	free_list(t_basic_list *node, void (*f)(void *));

/*	utils/handler.list.c		*/
void	add_prev(t_basic_list **list);
void	add_back(t_basic_list **list, t_basic_list *new);
#endif