/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:34:53 by dacortes          #+#    #+#             */
/*   Updated: 2023/09/12 16:30:25 by dacortes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_MINI_H
# define SHELL_MINI_H

# include "../lib/libft/libft.h"
# include "../lib/libft/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <limits.h>
# include <errno.h>
// ================================= MACROS ================================= //
/* Utils */
# define DQU	34
# define QUO	39
# define RDE	60
# define RDS	62
/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1
/* tokens types */
# define T_EXP 1
# define T_TXT 2
/* Inputs */
# define KEY 1
# define VAL 2
/* Error */
# define E_SPC -2
# define E_ARG 1
# define E_MEM 2
# define E_NSF 3
# define E_PRR 4
# define E_PNF 5
# define E_EXP 6
# define E_PRM 126
# define E_CNF 127
# define EX 255
// ================================= COLORS ================================= //
# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue
# define T "\033[1;35m"	   //Turquesa
# define C "\033[1;36m"    //Cyan
# define O "\033[38;5;208m" //orange
# define F "\033[38;5;128m"  //purple
// ================================= STRUCTURES ============================= //

typedef struct s_aux
{
	int		i;
	int		j;
	int		k;
	int		c;
	int		key;
	int		val;
	int		eql;
	int		in_qu;
	char	*e;
	char	*tmp;
	char	*_key;
	char	*_val;
}	t_aux;

/* pipe, quotes, double quotes */
typedef struct s_token
{
	int				type;
	int				argc;
	char			*arg;
	struct s_token	*next;
}	t_token;
/* line to pipe */
typedef struct s_line
{
	int				argc;
	char			**argv;
	char			*line;
	t_token			*tk;
	struct s_line	*next;
}	t_line;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				eql;
	struct s_env	*next;
}	t_env;

typedef struct s_mini
{
	int		size;
	char	*user;
	char	*old;
	char	*dir;
	t_env	*env;
}	t_mini;

// ================================= FUNCTIONS ============================== //

/* src/built-ins/unset.c*/
int		unset(int *size, t_env **env, char *key);
/* src/built-ins/pwd.c */
int		pwd(void);
/* src/built-ins/cd.c */
int		cd(char *path, t_mini **sh);
int		ft_cd(t_line *ln, t_mini **sh);
/* src/built-ins/exit.c */
int		ft_exit(t_line **ln, t_mini *sh, char **argv, int argc);
/* src/built-ins/env.c */
void	_env(t_env *env);
int		init_env(t_mini *sh, char **env);
int		add_key(t_mini *sh, char *key, char *val, int eql);
/* src/built-ins/export.c */
void	show_export(t_env *env);
int		_export(t_mini *sh, char *inp);
/* scr/utils.c */
char	*search_env(t_env *env, char *key, int type);
char	*ft_strdup_exit(const char *s1);
char	*ft_strrep(const char *inp, size_t start, size_t end, char *rep);
char	*ft_strndup(const char *src, size_t n);
/* parse/line.c */
int		ft_line(char *inp, t_line **ln, t_env *env);
/* parse/utils_line.c */
int		clear_ln(t_line **ln);
void	show_line(t_line *ln);
char	**convert_to_argv(t_line *ln);
int		add_line(t_line **ln, t_token *tk, char	*line);
int		type_expand(char *inp, t_aux *a, t_token **tk, int type);
/* parse/token.c test */
void	show_tokens(t_line *ln);
int		clear_tk(t_token **tk);
int		expand_tk(t_token **tk, t_env *env);
int		add_token(t_token **tk, char *arg, int type, int *count);
/* */
int		clear(t_mini *sh);
int		msg_error(int e, int exit_, char *cm);
#endif