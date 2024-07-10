/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:42:35 by dacortes          #+#    #+#             */
/*   Updated: 2024/07/10 18:01:46 by dacortes         ###   ########.fr       */
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
# define TRUE   1
# define FALSE  0
# define ERROR  -1

/* error messages */
# define MINI "\033[1;31mmini rush plus\033[m"

typedef struct s_command_lines t_command_lines;
typedef struct s_minishell t_minishell;
typedef struct s_get_line t_get_line;
typedef struct s_token t_token;
typedef struct s_env t_env;

enum error_code
{
    SYNTAX,
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
    char *read_line;
    char **split_line;
};

struct s_command_lines
{
    short    pre;
    char    *line;
    t_token *token;
};

struct s_token
{
    short type;
	short is_quote;
    char *content;
    t_token *next;
};

struct s_env // array to array char **
{
	char	*key;
	char	*value;
	short	eql;
    t_env *next;
};

struct s_minishell
{
	int				status;
	t_get_line		get_line;
	t_env			*env;
    t_token         *token;
	t_command_lines	*cmd_lines;
};



/******************************************************************************/
/*                            FUNCTIONS                                       */
/******************************************************************************/

/* built-ins/env.c */
t_env	*init_env(char **env);
int		clear_env(t_env **env);
/* utils/clear_list.c */
int     clear_token(t_token **token);
/* utils/handler.list.c */
void	add_back(void **list, void *new, size_t size);
/* utils/printf_list.c */
int	printf_token(t_token *token);
/*  parsing/parsing.c */
int		parsing(t_minishell *mini);
#endif