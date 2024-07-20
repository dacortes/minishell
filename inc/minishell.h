/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/20 14:50:04 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                            MACROS                                          */
/******************************************************************************/

# include <libft.h>
# include <ft_printf.h>
# include <get_next_line.h>
# include <readline/readline.h>
# include <readline/readline.h>

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

# define TRUE       1
# define FALSE      0
# define ERROR      -1
# define FOUND      0
# define NOT_FOUND  -1

/* error messages */
# define MINI "\033[1;31mmini rush plus: \033[m"
# define ERR_MALLOC "error trying to allocate memory"
# define ERR_SYNTAX "syntax error near unexpected token"
# define ERR_ARGUMENT "too many arguments"

typedef struct s_command_lines t_command_lines;
typedef struct s_minishell t_minishell;
typedef struct s_get_line t_get_line;
typedef struct s_token t_token;
typedef struct s_env t_env;

enum error_code
{
    MALLOC=1,
    SYNTAX,
    ARGUMENT,
};

enum tokens_types
{
    OR,
    AND,
	ARG,
    PIPE,
    R_IN,
    R_OUT,
    R_APP,
    R_HER,
    EXPAN,
    S_SHELL,
};

struct s_get_line
{
    char	*read_line;
    char	**split_line;
};

struct s_command_lines
{
    short	pre;
    char	*line;
    t_token	*token;
};

struct s_token
{
    short	type;
	short	is_quote;
    char	*content;
    int		has_space;
    t_token *next;
};

struct s_env // array to array char **
{
	char	*key;
	char	*value;
	short	eql;
    t_env	*next;
};

struct s_minishell
{
	int				status;//se usa
    int				num_pipes;//-------
	t_get_line		get_line;//se usa
	t_env			*env;//se usa
    t_token			*token;//se usa
	t_command_lines	*cmd_lines;//-------
};



/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

/*	built-ins/env.c				*/
t_env	*init_env(char **env);
int		clear_env(t_env **env);
int		_env(t_env *env, int num_commands);


/*  built-ins/unset.c */
int     _unset(t_env **env, char *key);



/*	utils/clear_list.c			*/
int		clear_token(t_token **token);

/*	utils/errors.c				*/
char	*error_normalization(char *input);
int	    error_msg(int error, int code_exit, char *input);

/*	utils/handler.list.c		*/
void	add_back(void **list, void *new, size_t size);
/*	utils/printf_list.c			*/
int		printf_env(t_env *env);
int		printf_token(t_token *token);

/*	parsing/add_token_type.c	*/
int		init_token(t_token **token, char *content, char *del, int space);
int		metacharacters(t_token **token, char *line, char *del, int *pos);
int		not_metacharacters(t_token **token, char *line, char *del, int *pos);
/*	parsing/parsing.c			*/
int		parsing(t_minishell *mini);
/*	parsing/utils.c				*/
int		is_metacharacters(char c);
short	get_type(char *flag, char *content);
int		set_space(char *line, int *pos, char *del);
int		get_end_not_metacharacters(char *str);
int		get_end_token(char *str, char *del, int *pos, int size_del);
#endif