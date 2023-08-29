/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcespede <fcespede@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:34:53 by dacortes          #+#    #+#             */
/*   Updated: 2023/08/29 14:55:01 by fcespede         ###   ########.fr       */
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
	int		key;
	int		val;
	int		eql;
	char	*_key;
	char	*_val;
}	t_aux;

/* pipe, quotes, double quotes */
typedef struct s_token
{
	int				type;
	char			*arg;
	struct s_token	*next;
}	t_token;

/* get_cmd*/
typedef struct s_cmd
{
	int		type;
	char	*cmd;
	char	*arg;
}	t_cmd;

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
int	unset(int *size, t_env **env, char *key);
/* src/built-ins/pwd.c */
int	pwd(void);
/* src/built-ins/cd.c */
int	cd(char *path, t_mini **sh);
/* src/built-ins/exit.c */
void	ft_exit(char *input);
/* src/built-ins/env.c */
void	_env(t_env *env);
int		init_env(t_mini *sh, char **env);
int		add_key(t_mini *sh, char *key, char *val, int eql);
/* src/built-ins/export.c */
void	show_export(t_env *env);
int		_export(t_mini *sh, char *inp);
/* scr/utils.c */
int		is_close(char *str, char delimiter);
char	*search_env(t_env *env, char *key, int type);
char	*ft_strdup_exit(const char *s1);
/* parse/token.c test */
// int		token(char *inp, int *e);
int		token(char *inp);
/* test */
int		clear(t_mini *sh);
int		msg_error(int e, int exit_, char *cm);

#endif