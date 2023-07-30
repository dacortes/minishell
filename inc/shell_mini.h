/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_mini.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacortes <dacortes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:34:53 by dacortes          #+#    #+#             */
/*   Updated: 2023/07/30 10:54:12 by dacortes         ###   ########.fr       */
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
# define D_QUOTES	34
# define QUOTES		39
# define BLASH		92
/* Outputs */
# define SUCCESS 0
# define FALSE	 0
# define TRUE	 1
# define ERROR 	-1
# define E_EXIT  1
/* Types
1=pipe
2=<< >>
3=txt
4=file
5=command
6=dolar
7=space
*/
# define PP 1
# define RD 2
# define TX 3
# define FL 4
# define CM 5
# define DL 6
# define SP 7
/* Inputs */
# define VAR 1
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
typedef struct s_axu
{
	char	*var;
	char	*val;
	int		eql;
	int		len_r;
	int		len_k;
}	t_axu;

/* pipe, quotes, double quotes */
typedef struct s_token
{
	int				t_qu;
	int				t_dq;
	int				t_dl;
	int				type;
	char			*arg;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*var;
	char			*val;
	int				eql;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	t_token	*tk;
}	t_parse;

typedef struct s_mini
{
	int		e_size;
	char	*user;
	char	*old;
	char	*dir;
	t_env	*env;
}	t_mini;

// ================================= FUNCTIONS ============================== //
/* built-ins/cd.c */
int		cd(char *path, t_mini **sh);
/* built-ins/env */
int		add_var_env(t_mini *sh, char *var, char *val, int eql);
int		new_var_env(t_mini *shell, char *var);
char	*find_var_env(t_env *env, char *find, int type);
void	printf_env(t_env *env);
/* buuild-ins/exit.c */
int		ft_exit(char *input);
/* built-ins/export.c */
int		replace_val(t_env *env, char *var, char *val, int eql);
int		_export(t_mini *sh, char *str);
void	print_export(t_env *env);
/* built-ins/cpwd.c */
int		pwd(void);
/* built-ins/unset  */
int		unset(int *size, t_env **env, char *var);
/* parse/tokens */
int		ft_is_space(int c);
int		ignore_sp(char *str);
/* parse/utils */
int		token(/*t_token *tk, */char *inp);
/* test */
void	magic_node(t_mini *sh);
int		msg_error(int e, int exit_, char *cm);

#endif